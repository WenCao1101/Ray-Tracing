#include"Shape.h"

inline bool rayTriangleIntersect(
	const glm::vec3& orig, const glm::vec3& dir,
	const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
	float& t, float& u, float& v) {
	auto edge1 = v1 - v0;
	auto edge2 = v2 - v0;
	auto h = cross(dir, edge2);
	auto a = dot(edge1, h);
	if (a > -kEpsilon && a < kEpsilon) {
		return false;  // This ray is parallel to this triangle.
	}
	float f = 1.0f / a;
	auto s = orig - v0;
	u = f * dot(s, h);
	if (u < 0.0 || u > 1.0) {
		return false;
	}
	auto q = cross(s, edge1);
	v = f * dot(dir, q);
	if (v < 0.0 || u + v > 1.0) {
		return false;
	}
	// At this stage we can compute t to find out where the intersection point is on the line.
	t = f * dot(edge2, q);
	if (t > kEpsilon) {
		return true;
	}
	else  // This means that there is a line intersection but not a ray intersection.
		return false;
}
//using namespace glm;
Mesh::Mesh(std::vector<Triangle> const& triangles) : triangles(triangles) {
}
bool Mesh::hit(Ray& ray, double t_min, double t_max, IsectInfo& rh) const
{
	int idx = rh.tri_idx;
	vec3 n;
	float t, v, w;
	if (rayTriangleIntersect(ray.orig, ray.dir, triangles[idx].vertex[0], triangles[idx].vertex[1], triangles[idx].vertex[2], t, v, w))
	{
		// r.has_hit = true;
		ray.dist = t;
		ray.u = v;
		ray.v = w;
		rh.mat_obj = make_shared<ObjMaterial>(triangles[idx].mat_ptr);

		/*   if (has_normals())
		   {
			   face = normals.face(prim_idx);
			   r.hit_normal = normalize(normals.vertex(face[0]) * (1.0f - v - w) + normals.vertex(face[1]) * v + normals.vertex(face[2]) * w);
		   }
		   else
			   r.hit_normal = normalize(n);

		   r.hit_object = this;
		   r.hit_face_id = prim_idx;
		   //if(material->has_texture && texcoords.no_faces() > 0)
		   //{
		   //  face = texcoords.face(prim_idx);
		   //  hit.texcoord = u*texcoords.vertex(face.x) + v*texcoords.vertex(face.y) + w*texcoords.vertex(face.z);
		   //}*/
		return true;
	}
	return false;
}

void Mesh::transform(const mat4& m)
{
	for (unsigned int i = 0; i < triangles.size(); ++i)
	{
		triangles[i].vertex[0] = m * glm::vec4(triangles[i].vertex[0], 1);
		triangles[i].vertex[0] = m * glm::vec4(triangles[i].vertex[1], 1);
		triangles[i].vertex[0] = m * glm::vec4(triangles[i].vertex[2], 1);
		triangles[i].normal[0] = m * glm::vec4(triangles[i].normal[0], 0);
		triangles[i].normal[1] = m * glm::vec4(triangles[i].normal[1], 0);
		triangles[i].normal[2] = m * glm::vec4(triangles[i].normal[2], 0);
	}

}
glm::vec3 Triangle::get_midpoint() const {
	return glm::vec3((bbox.max.x + bbox.min.x) / 2, (bbox.max.y + bbox.min.y) / 2, (bbox.max.z + bbox.min.z) / 2);
}

/*BBox Mesh::get_primitive_bbox(unsigned int prim_idx) const
{
	BBox bbox;

	bbox.add_point(triangles[prim_idx].vertex[0]);
	bbox.add_point(triangles[prim_idx].vertex[1]);
	bbox.add_point(triangles[prim_idx].vertex[2]));
	return bbox;
}*/
BBox Triangle::get_bounding_box() {
	BBox bbox;
	bbox.computeBBoxFromOriginalPointSet(vertex);
	return bbox;
}
BBox Mesh::get_bounding_box() {
	BBox bbox;
	//bbox.computeBBoxFromOriginalPointSet(vertex);
	for (int i = 0; i < triangles.size(); i++)
	{
		bbox.add_point(triangles[i].vertex[0]);
		bbox.add_point(triangles[i].vertex[1]);
		bbox.add_point(triangles[i].vertex[2]);
	}
	return bbox;
}
/* unsigned int Mesh::find_material(const string& name) const
{
	for (unsigned int i = 0; i < materials.size(); ++i)
	{
		if (materials[i].name == name)
			return i;
	}
	return 0;
}*/