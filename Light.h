#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include "Ray.h"
#define GLM_FORCE_RADIANS
//#include"Ray.h"
#ifndef EPSILON
#define EPSILON          5.e-5f  /* epsilon */
#endif
class Ray;
class Mesh;
class Light {
public:
    // Light Interface
	virtual bool sample(const vec3& position) const=0;
    Light() {}
 //   virtual ~Light();
   
 //  int samples;

};

class PointLight:public Light {
public:
	PointLight(glm::vec3 pos, glm::vec3 light) : pos(pos), light(light) {}

	glm::vec3 at(glm::vec3 const& point) const {
		return light / glm::distance(point, pos);
	}
	bool sample(const vec3& position) const override;
	Ray ray_from(glm::vec3 const& point) const {
		auto d = pos - point;
		float t_max = length(d);
		return Ray(point, d / t_max, EPSILON, t_max);
	}
	glm::vec3 pos;
	glm::vec3 light;
};

class AreaLight : public Light
{
public:
	bool sample(const vec3& position) const override;
	const Mesh* mesh;
	glm::vec3 get_emission_obj(int triangle_id) const;
};

#endif
