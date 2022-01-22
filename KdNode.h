#include "Shape.h"

#ifndef KDNODE_H_
#define KDNODE_H_

/*struct IsectInfo
{
	glm::vec3 position;
	glm::vec3 normal;
	Mesh* mesh_I;
	float tNear = kInfinity;
	bool isEmpty;
	glm::vec3 albedo;
	glm::vec3 Ka, Kd, Ks, Tr;
	float n, ior, illum;
	//MaterialType type;
	//int type;
};*/
/*struct AccObj
{
	AccObj() :mesh(0), prim_idx(0) {}
	AccObj(const Mesh* meshss, int prim_idx) :mesh(meshss), prim_idx(prim_idx),bbox(meshss->triangles[prim_idx].bbox) {}
   const Mesh* mesh;
	BBox bbox;
 int prim_idx;
};*/

class KDNode
{
public:
	BBox bbox;
	KDNode* left;
	KDNode* right;
	vector<Mesh*> Meshes;
	Mesh* meshes;
	//KDNode() {};
	KDNode(vector<Mesh*> Meshes) :left(NULL), right(NULL), Meshes(Meshes) {}

	KDNode() :left(NULL),right(NULL),meshes(NULL) {}
    KDNode* build(int depth) const;
	bool kIntersect(const KDNode* node, const glm::vec3& orig, const glm::vec3& dir, IsectInfo* isct)const;
	void init();
};


#endif