#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>
//#include"ObjMaterial.h"
//#include"Shape.h"
using namespace glm;

class ObjMaterial;
class Triangle;


class Ray {
public:
    Ray() {}
    Ray(const vec3& origin, const vec3& direction)
        : orig(origin), dir(direction), tm(0), tmin(0.01f), tmax(std::numeric_limits<float>::infinity())
    {}

    Ray(const vec3& origin, const vec3& direction, float time)
        : orig(origin), dir(direction), tm(time),tmin(0.01f),tmax(std::numeric_limits<float>::infinity())
    {}
    Ray(const vec3& origin, const vec3& direction, float tmin, float tmax)
        : orig(origin), dir(direction),tmin(tmin), tmax(tmax)
    {}
    Ray(const vec3& origin, const vec3& direction, float time,float tmin,float tmax)
        : orig(origin), dir(direction), tm(time), tmin(tmin), tmax(tmax)
    {}

    vec3 origin() const {return orig; }
    vec3 direction() const {return dir; }
    float time() const {return tm; }

    vec3 at(float t) const {
        return orig + t * dir;
    }
    ObjMaterial* get_material() const;
     Triangle* hit_object;
    float u, v;            // uv-coordinates on current surface
    vec3 orig;
    vec3 dir;
    float tm;
    float dist;            // Distance from origin to current intersection
    mutable  float tmin, tmax;
};













#endif
