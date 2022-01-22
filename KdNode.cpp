#include "KdNode.h"
#include"Shade.h"
void KDNode::init() {
	for (unsigned int i = 0; i < Meshes.size(); ++i)
	{
		bbox.extendBy(Meshes[i]->get_bounding_box());
	}

	for (unsigned int i = 0; i < Meshes.size(); ++i)
	{
		meshes = Meshes[0];
		if (Meshes.size() == i + 1)
			return;
		else {
			Mesh* obj = Meshes[i + 1];
			int no_of_triangles;
			if (meshes != meshes || meshes == NULL)
				no_of_triangles = 0;
			else
				no_of_triangles = meshes->triangles.size();
			int no_of_triangles_objects;
			if (obj != obj || obj == NULL)
				no_of_triangles_objects = 0;
			else
				no_of_triangles_objects = obj->triangles.size();
			if (no_of_triangles + no_of_triangles_objects <= 0)
			{
				meshes = NULL;
				return;
			}
			else
				//(*meshes).triangles.resize(no_of_triangles+ no_of_triangles_objects);
				for (int j = 0; j < no_of_triangles_objects; j++)
					meshes->triangles.push_back(obj->triangles[j]);
		}
	}

	return;

}




KDNode* KDNode::build(int depth) const {
	//std::vector<Triangle> triangles1;
	KDNode* node = new KDNode();
	node->meshes = meshes;
	node->left = NULL;
	node->right = NULL;
	node->bbox = BBox();


	if (meshes->triangles.size() == 0) {

		return node;
	}
	if (meshes->triangles.size() == 1) {
		node->bbox = meshes->triangles[0].get_bounding_box();
		node->left = new KDNode();
		node->right = new KDNode();
		node->left->meshes = new Mesh();
		node->right->meshes = new Mesh();
		return node;
	}

	node->bbox = meshes->triangles[0].get_bounding_box();

	for (int i = 1; i < meshes->triangles.size(); i++) {
		//node->bbox.extendBy(meshs->triangles[i].vertex[j]);
		node->bbox.extendBy(meshes->triangles[i].get_bounding_box());
	}

	glm::vec3 midPoint = glm::vec3(0, 0, 0);
	for (int i = 0; i < meshes->triangles.size(); i++) {
		//	for (int j = 0; j < 3; j++) {
		midPoint = midPoint + meshes->triangles[i].get_midpoint();

		//	}
	}

	midPoint /= meshes->triangles.size();
	Mesh* leftMeshes = new Mesh();
	Mesh* rightMeshes = new Mesh();

	int axis = node->bbox.longest_axis();
	for (int i = 0; i < meshes->triangles.size(); i++) {

		switch (axis) {
		case 0:
			midPoint.x >= meshes->triangles[i].get_midpoint().x ? rightMeshes->triangles.push_back(meshes->triangles[i]) : leftMeshes->triangles.push_back(meshes->triangles[i]);
			break;
		case 1:
			midPoint.y >= meshes->triangles[i].get_midpoint().y ? rightMeshes->triangles.push_back(meshes->triangles[i]) : leftMeshes->triangles.push_back(meshes->triangles[i]);
			break;
		case 2:
			midPoint.z >= meshes->triangles[i].get_midpoint().z ? rightMeshes->triangles.push_back(meshes->triangles[i]) : leftMeshes->triangles.push_back(meshes->triangles[i]);
			break;
		}
	}

	if (leftMeshes->triangles.size() == 0 && rightMeshes->triangles.size() > 0) leftMeshes = rightMeshes;
	if (rightMeshes->triangles.size() == 0 && leftMeshes->triangles.size() > 0) rightMeshes = leftMeshes;
	int matches = 0;

	for (int i = 0; i < leftMeshes->triangles.size(); i++) {
		for (int j = 0; j < rightMeshes->triangles.size(); j++) {
			if ((leftMeshes->triangles[i].vertex[0] == rightMeshes->triangles[j].vertex[0]) &&
				(leftMeshes->triangles[i].vertex[1] == rightMeshes->triangles[j].vertex[1]) &&
				(leftMeshes->triangles[i].vertex[2] == rightMeshes->triangles[j].vertex[2]))
			{
				matches++;
			}

		}
	}



	if ((double)matches / leftMeshes->triangles.size() < 0.5 && (double)matches / rightMeshes->triangles.size() < 0.5) {

		node->left = build(depth + 1);
		node->right = build(depth + 1);
	}
	else {
		node->left = new KDNode();
		node->right = new KDNode();
		node->left->meshes = new Mesh();
		node->right->meshes = new Mesh();
	}

	return node;
}

bool KDNode::kIntersect(const KDNode* node, const glm::vec3& orig, const glm::vec3& dir, IsectInfo* isct) const {
	bool hit_tri = false;
	//IsectInfo* isct;
	uint32_t idx = 0;
	glm::vec3 vchit;
	isct->isEmpty = true;


	if (node->bbox.bIntersect(orig, dir, &vchit)) {
		//如果子节点还有三角形，递归两边并检查是否有交
		if (node->left->meshes->triangles.size() > 0 || node->right->meshes->triangles.size() > 0) {
			bool hitleft = kIntersect(node->left, orig, dir, isct);
			bool hitright = kIntersect(node->right, orig, dir, isct);
			return hitleft || hitright;
		}

		else {
			//到达子节点
			float t = kInfinity, u = 0, v = 0;
			for (int i = 0; i < node->meshes->triangles.size(); i++) {
				//如果有交，返回交点以及法向
				if (rayTriangleIntersect(orig, dir, node->meshes->triangles[i].vertex[0], node->meshes->triangles[i].vertex[1], node->meshes->triangles[i].vertex[2], t, u, v)) {
					if (t < isct->tNear) {
						hit_tri = true;
						isct->tNear = t;
						vec3 e0 = node->meshes->triangles[i].vertex[1] - node->meshes->triangles[i].vertex[0];
						vec3 e1 = node->meshes->triangles[i].vertex[0] - node->meshes->triangles[i].vertex[2];
						isct->mat_obj = make_shared<ObjMaterial>(node->meshes->triangles[i].mat_ptr);
						if (node->meshes->triangles[i].hasnormal == false)
							isct->normal = -normalize(cross(e0, e1));
						isct->normal = normalize(node->meshes->triangles[i].normal[0] * (1 - u - v) + node->meshes->triangles[i].normal[1] * u
							+ node->meshes->triangles[i].normal[2] * v);
						isct->p = orig + isct->tNear * dir;
						isct->triangle_I = &node->meshes->triangles[i];
						isct->mesh = node->meshes;
						auto shade_type = node->meshes->triangles[i].mat_ptr.type;
						switch (shade_type) {
						case kDiffuse:
							isct->mat_ptr = std::make_shared<Lambertian>();
							break;
						case kReflective:
							isct->mat_ptr = std::make_shared<Mirror>();
							break;
						case kRefractive:
							isct->mat_ptr = std::make_shared<Glass>();
							break;
						case Light:
							isct->mat_ptr = std::make_shared<Diffuse_light>();
							break;
						}
						//return true;
					}
				}
				//idx++;
			}
			if (hit_tri) {

				//	*result = minResult;
				return true;
			}

		}
	}


	return false;
}

