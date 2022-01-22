#ifndef SHADE_H
#define SHADE_H
//#include"Ray.h"
#include"Utility.h"
#include"ObjMaterial.h"
#include"Onb.h"
#include"Iteraction.h"
/*class IsectInfo;
class hit_record;
class scatter_record;*/
class Shade {
public:
    Shade() {}
   /* virtual vec3 emitted(const hit_record& rec) const {
        return vec3(0, 0, 0);
    }*/
    
  virtual vec3 get_emission(const Ray& r) const {
       return vec3(1/PI, 1 / PI, 1 / PI);
   }
  
    virtual float scattering_pdf(
        const Ray& r_in, const hit_record& rec, const Ray& scattered
    ) const {
        return 0;
    }
    virtual bool scatter( const Ray& r_in, const IsectInfo &rec, vec3& attenuation, scatter_record& srec) const = 0;
    float bias = 0.001;
};

class Lambertian : public Shade {
public:
  //  Lambertian(const vec3& a) : albedo(a) {}

    Lambertian() {}
    vec3 get_diffuse(const Ray& r)const;
   
  virtual bool scatter(const Ray& r_in, const IsectInfo &rec, vec3& attenuation, scatter_record& srec
    ) const override {
     // rec.normal = dot(rec.normal, r_in.dir) < 0 ? rec.normal : rec.normal * -1.0f;
      srec.is_specular = false;
      Onb uvw;
      if(dot(rec.normal, r_in.dir) < 0)
      uvw.build_from_w(rec.normal);
      else
          uvw.build_from_w(rec.normal*-1.0f);
      auto direction = uvw.local(random_cosine_direction());
   //  vec3 albedo= get_diffuse(r_in);
      vec3 albedo = rec.mat_obj->diffuse;
      // auto scatter_direction = rec.normal + random_unit_vector();
       if (near_zero(direction))
           direction = rec.normal;
      
        srec.specular_ray = Ray(rec.p, normalize(direction));
        srec.attenuation = albedo;

   srec.pdf_val = dot(uvw.w(), srec.specular_ray.direction()) / PI;
        return true;
    }
  float scattering_pdf(
      const Ray& r_in, const hit_record& rec, const Ray& scattered
  ) const override {
      float cosine;
      if (dot(rec.normal, r_in.dir) < 0)
      cosine = dot(rec.normal, normalize(scattered.direction()));
      else
          cosine = dot(rec.normal*-1.0f, normalize(scattered.direction()));
      return cosine < 0 ? 0 : cosine / PI;
  }

};
class Mirror :public Shade {
public:
    Mirror() {}
    bool scatter(
        const Ray& r_in, const IsectInfo& rec, vec3& attenuation, scatter_record& srec
    ) const;
    
       
};
class Glass :public Shade {
public:
    Glass() {}
    bool scatter(
        const Ray& r_in, const IsectInfo & rec, vec3& attenuation, scatter_record& srec
    ) const;
    

};
class Metal : public Shade {
public:
  //  Metal(float f) : fuzz(f < 1 ? f : 1) {}
    vec3 get_diffuse(const Ray& r)const;
    bool scatter(
        const Ray& r_in, const IsectInfo & rec, vec3& attenuation, scatter_record& srec
    ) const;
   
  //  vec3 albedo;
  // float fuzz;
};

class Dielectric : public Shade {
public:
    Dielectric(float index_of_refraction) : ir(index_of_refraction) {}
    bool scatter(
        const Ray& r_in, const IsectInfo & rec, vec3& attenuation, scatter_record& srec
    ) const;
    float ir; // Index of Refraction

private:
    static float reflectance(float cosine, float ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
    
};

class Diffuse_light : public Shade {
public:

    Diffuse_light() {}
    vec3 get_emission(const Ray& r);
 //   Diffuse_light(vec3 c) : emit(c) {}
    bool scatter(
        const Ray& r_in, const IsectInfo& rec, vec3& attenuation, scatter_record& srec
    ) const;
   

  /*  virtual vec3 emitted(const hit_record& rec) const override {
        if (!rec.front_face)
            return rec;
        else
            return vec3(0, 0, 0);
    }*/

   // vec3 emit;
    
};






#endif
