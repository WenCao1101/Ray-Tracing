#ifndef SHAPES_H
#define SHAPES_H
//#include"Ray.h"
#include <iostream>
//#include"Utility.h"
#include"Iteraction.h"
//#include"Shade.h"
//#include"KdNode.h"
#include <vector>
#include "BBox.h"
#include"ObjMaterial.h"
//#include"AABB.h"
//using namespace glm;
static const float kEpsilon = 1e-8;
class KdNode;
//class ObjMaterial;
class Shape {
public:
	Shape() {}

	virtual ~Shape() = default;
	// virtual bool bounding_box(AABB& output_box) const = 0;
	virtual bool hit(Ray& ray, double t_min, double t_max, IsectInfo& rh) const = 0;
	virtual double pdf_value(const vec3& o, const vec3& v) const {
		return 0.0;
	}

	virtual vec3 random(const vec3& o) const {
		return vec3(1, 0, 0);
	}


};

class Sphere :public Shape {
public:
	Sphere() {}
	Sphere(vec3 cen, float r)
		: center(cen), radius(r) {
		//mat_ptr = nullptr;
	};
	Sphere(vec3 cen, double r, shared_ptr<Shade> m)
		: center(cen), radius(r), mat_ptr(m) {};

	/*  virtual bool bounding_box(AABB& output_box) const override {
		  output_box = AABB(
			  center - vec3(radius, radius, radius),
			  center + vec3(radius, radius, radius));
		  return true;

	  }*/



	bool hit(
		Ray& r, double t_min, double t_max, IsectInfo& rec) const override {
		vec3 oc = r.origin() - center;
		auto a = r.direction()[0] * r.direction()[0] + r.direction()[1] * r.direction()[1] + r.direction()[2] * r.direction()[2];
		auto half_b = dot(oc, r.direction());
		auto c = oc[0] * oc[0] + oc[1] * oc[1] + oc[2] * oc[2] - radius * radius;

		auto discriminant = half_b * half_b - a * c;
		if (discriminant < 0) return false;
		auto sqrtd = sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (-half_b - sqrtd) / a;
		if (root < t_min || t_max < root) {
			root = (-half_b + sqrtd) / a;
			if (root < t_min || t_max < root)
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		vec3 outward_normal = (rec.p - center) * static_cast<float>(1 / radius);
		rec.set_face_normal(r, outward_normal);
		rec.mat_ptr = mat_ptr;

		return true;
	};

public:
	vec3 center;
	float radius;
	shared_ptr<Shade> mat_ptr;
};
bool rayTriangleIntersect(
	const glm::vec3& orig, const glm::vec3& dir,
	const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
	float& t, float& u, float& v);

class Triangle :public Shape {
public:
	//Triangle() {}
	Triangle() {
		for (int i = 0; i < 3; i++) {
			vertex[i] = vec3(0.0f);
		}
	}

	bool hit(Ray& ray, double t_min, double t_max, IsectInfo& rh)  const override {
		float t, v, w;
		return rayTriangleIntersect(ray.orig, ray.dir, vertex[0], vertex[1], vertex[2], t, v, w);
	}
	glm::vec3 faces[3];
	glm::vec3 vertex[3];
	glm::vec3 normal[3];
	BBox bbox;
	glm::vec3 get_midpoint() const;
	BBox get_bounding_box();
	ObjMaterial mat_ptr;
	int mtl;
	bool hasnormal;
};
class Mesh : public Shape {
public:
	// Mesh() {}
	 /*bool rayTriangleIntersect(
		 const glm::vec3& orig, const glm::vec3& dir,
		 const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
		 float& t, float& u, float& v);*/
	bool hit(Ray& ray, double t_min, double t_max, IsectInfo& rh) const override;
	void transform(const mat4& m);
	unsigned int find_material(const string& name) const;
	Mesh(std::vector<Triangle> const& triangles);
	Mesh() = default;
	BBox get_bounding_box();
	std::vector<Triangle> triangles;
	/// Vector of materials
  //  std::vector<ObjMaterial> materials;

};

#endif
