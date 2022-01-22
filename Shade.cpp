#include"Shade.h"
//#include"Ray.h"
//#include"Ray.cpp"
#include"Shape.h"
#include"ObjMaterial.h"
vec3 Lambertian::get_diffuse(const Ray& r)const {
    ObjMaterial* m = r.get_material();
    return m ? r.get_material()->diffuse : vec3(0.0f);
}

vec3 Metal::get_diffuse(const Ray& r)const {
    ObjMaterial* m = r.get_material();
    return m ? r.get_material()->diffuse : vec3(0.0f);
}


bool Mirror::scatter(
    const Ray& r_in, const IsectInfo& rec, vec3& attenuation, scatter_record& srec
) const {
    bool outside = dot(r_in.dir, rec.normal) > 0;
    vec3 reflect_dir;
    if(outside)
    reflect_dir = normalize(reflect(normalize(r_in.direction()), rec.normal));
    else
     reflect_dir = normalize(reflect(normalize(r_in.direction()), rec.normal*-1.0f));
    srec.specular_ray = Ray(outside ? rec.p - bias* rec.normal : rec.p + bias* rec.normal, reflect_dir);
    srec.is_specular = true;
    return true;
}
bool Glass::scatter(
    const Ray& r_in, const IsectInfo& rec, vec3& attenuation, scatter_record& srec
) const {
    float R; float ior;
    srec.is_specular = true;
    srec.is_glass = true;
 //   ObjMaterial* m = r_in.get_material();
   // if (m != NULL)
    ior = rec.mat_obj->ior;
     //   ior = m->ior;
    fresnel(r_in.direction(), rec.normal, ior, R);
    bool outside = dot(r_in.dir, rec.normal) < 0;
    srec.Fresnel = R;
    vec3 reflect_dir = normalize(reflect(normalize(r_in.direction()), rec.normal));
    srec.Reflec_ray = Ray(outside ? rec.p - bias* rec.normal : rec.p + bias* rec.normal, reflect_dir);
    vec3 refract_dir = normalize(refract(normalize(r_in.direction()), rec.normal, ior));
    srec.Refract_ray = Ray(outside ? rec.p - bias* rec.normal : rec.p + bias* rec.normal, refract_dir);
    return true;
};

bool Metal::scatter(
    const Ray& r_in, const IsectInfo& rec, vec3& attenuation, scatter_record& srec
) const {
    // compute fresnel
    float R; float ior;
    ObjMaterial* m = r_in.get_material();
    if (m != NULL)
        ior = m->ior;
    fresnel(r_in.direction(), rec.normal, ior, R);
    bool outside = dot(r_in.dir, rec.normal) < 0;;
    if (random_double() < R) {
        vec3 reflect_dir = normalize(reflect(normalize(r_in.direction()), rec.normal));
        srec.specular_ray = Ray(outside ? rec.p - bias : rec.p + bias, reflect_dir);
    }
    else {
        vec3 refract_dir = normalize(refract(normalize(r_in.direction()), rec.normal, ior));
        srec.specular_ray = Ray(outside ? rec.p - bias : rec.p + bias, refract_dir);

    }
    srec.is_specular = true;
    srec.pdf_ptr = nullptr;
    srec.attenuation = get_diffuse(r_in);
    return (dot(srec.specular_ray.direction(), rec.normal) > 0);
};
bool Dielectric::scatter(
    const Ray& r_in, const IsectInfo& rec, vec3& attenuation, scatter_record& srec
) const {
    srec.is_specular = true;
    srec.pdf_ptr = nullptr;
    srec.attenuation = vec3(1.0, 1.0, 1.0);
    float refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

    vec3 unit_direction = normalize(r_in.direction());
    float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3 direction;
    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);

    srec.specular_ray = Ray(rec.p, direction);
    return true;
};

 bool Diffuse_light::scatter(
    const Ray& r_in, const IsectInfo& rec, vec3& attenuation, scatter_record& srec
) const {
   /*  vec3 on_light = rec.mesh->get_bounding_box().min + rec.mesh->get_bounding_box().max;
    vec3 to_light=on_light - rec.p;
     srec.light_dist = to_light[0] * to_light[0] + to_light[1] * to_light[1] + to_light[2] * to_light[2];
     srec.light_dir = normalize(to_light);
    
  srec.light_are = (rec.mesh->get_bounding_box().Corners[0] - rec.mesh->get_bounding_box().Corners[1]).length() * (rec.mesh->get_bounding_box().Corners[0] - rec.mesh->get_bounding_box().Corners[2]).length();
   */
    return false;
}


vec3 Diffuse_light::get_emission(const Ray& r) {
    ObjMaterial* m = r.get_material();
    return m ? r.get_material()->ambient : vec3(0.0f);
}