#ifndef ITERACTION_H
#define ITERACTION_H
#include <glm/glm.hpp>
#include <memory>
#include"Ray.h"
//#include"ObjMaterial.h"
//class Ray;
using namespace std;
using namespace glm;
class Shade;
//class Ray;
class pdf;
class Mesh;
const static float kInfinity1 = std::numeric_limits<float>::max();
class hit_record {
public:
    hit_record(vec3 p, vec3 normal, shared_ptr<Shade> mat_ptr, double t, bool front_face):p(p), normal(normal), mat_ptr(mat_ptr), t(t), front_face(front_face){}
    hit_record() {}
    vec3 p;
    vec3 normal;
    shared_ptr<Shade> mat_ptr;
    double t;
    bool front_face;
    /*float t_min=0.0001f;
    float t_max=infinity;*/
    inline void set_face_normal(const Ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
    unsigned int tri_idx;
};
class IsectInfo:public hit_record
{public:
   /* IsectInfo(vec3 p,vec3 normal,shared_ptr<Shade> mat_ptr, double t, bool front_face, Mesh* mesh_I,
    float tNear, bool isEmpty,shared_ptr<ObjMaterial> mat_obj): hit_record(p,normal,mat_ptr,t,front_face),mesh_I(mesh_I),
    tNear(tNear),isEmpty(isEmpty), mat_obj(mat_obj){}*/
    IsectInfo(){}
    IsectInfo(bool f) :isEmpty(f) {};
    Triangle* triangle_I;
    Mesh* mesh;
    float tNear = kInfinity1;
    bool isEmpty;
    shared_ptr<ObjMaterial> mat_obj;
   // MaterialType type;
    //int type;
};
class scatter_record: public IsectInfo {
public:
   scatter_record() {}
    Ray specular_ray;
    bool is_specular;
    bool is_glass=false;
    vec3 attenuation;
    float pdf_val;
    Ray Reflec_ray;
    Ray Refract_ray;
    float Fresnel=1.0;
    shared_ptr<pdf> pdf_ptr;
    
};
/*
class hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};*/











#endif
