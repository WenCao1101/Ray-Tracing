#ifndef TRACER_H
#define TRACER_H
#include"Scene.h"
#include"Pdf.h"
#include"Light.h"
//#include"Utility.h"
//using namespace glm;
//class hittable_pdf;
class Tracer
{
public:
	Tracer(Scene s) :scene(s) {}
	Tracer(Scene s, std::vector<PointLight*> lights) :scene(s), lights(lights) {}
	vec3 Li(Ray& ray, const vec3& background, int depth) const {
		//Sphere a(vec3(0, 0, -1), 0.5);
		if (depth < max_depth) {
			IsectInfo rec;
			if (!scene.hit(ray, 0.001, infinity, rec)) {
				return background;//background color
			}
			else {
				scatter_record srec;
				vec3 attenuation;
				vec3 emitted = rec.mat_obj->ambient;
				//vec3 emitted = rec.mat_ptr->get_emission(ray);
				float pdf_val(1.0);
				srec.pdf_val = 1.0f;
				if (!rec.mat_ptr->scatter(ray, rec, attenuation, srec)) {
					return emitted;
				}
				else
				{
					if (srec.is_specular && !srec.is_glass) {
						return Li(srec.specular_ray, background, depth + 1);
					}
					else {
						if (srec.is_specular && srec.is_glass)
						{
							return Li(srec.Reflec_ray, background, depth + 1) * srec.Fresnel + Li(srec.Refract_ray, background, depth + 1) * (1 - srec.Fresnel);
						}
						else {
							/*for (auto const& light : lights) {
								auto ray_l = light->ray_from(rec.p);
								if (dot(ray_l.dir, rec.normal) < 0)
									return emitted;
								if (fabs(ray_l.dir.y) < 0.001)
									return emitted;
								Ray scattered = ray_l;*/


								//	hittable_pdf light_pdf(lights, rec.p);
							Ray scattered = srec.specular_ray;
								//Ray scattered = Ray(rec.p, light_pdf.generate());
								//pdf_val = light_pdf.value(scattered.direction());
							
							//vec3 on_light = vec3(static_cast<float>(random_double(213, 343)), 554.0f, static_cast<float>(random_double(227, 332)));
							//vec3 to_light = on_light - rec.p;
							//auto distance_squared = to_light[0] * to_light[0] + to_light[1] * to_light[1] + to_light[2] * to_light[2];
							//to_light = normalize(to_light);
							
						/*	if (dot(to_light, rec.normal) < 0)
								return emitted;
							else {
							//	float light_area = (343 - 213) * (332 - 227);
								
								auto light_cosine = fabs(to_light.y);
								if (light_cosine < 0.000001)
									return emitted;
								else {
									/* vec3 target = rec.p + rec.normal + random_in_unit_sphere();
									 Ray r(rec.p, target - rec.p);*/
								/*	pdf_val = srec.light_dist / (light_cosine * light_area);
									Ray scattered = Ray(rec.p, to_light);*/
										//	cout << "depth=" << endl << "" << depth << endl;
					   //	cout << "scatter ray" << endl << "" << scattered.direction()[0] << endl << scattered.direction()[1] << endl << scattered.direction()[2] << endl;
						   //	return emitted + attenuation  * Li(srec.specular_ray, background, depth + 1);
										return emitted + srec.attenuation * rec.mat_ptr->scattering_pdf(ray, rec, scattered) * Li(scattered, background, depth + 1) / srec.pdf_val;
									//	return emitted + srec.attenuation * Li(scattered, background, depth + 1) / srec.pdf_val;

								
						}
						return vec3(0, 0, 0);
					}
					return vec3(0, 0, 0);
				}
				return vec3(0, 0, 0);
			}
			return vec3(0, 0, 0);
		}
		/* vec3 unit_direction = glm::normalize(ray.direction());
		 auto t = 0.5 * (unit_direction.y+1.0);
		 return static_cast<float>(1.0 - t) * vec3(1.0f, 1.0f, 1.0f) + static_cast<float>(t) * vec3(0.5f, 0.7f, 1.0f);*/
		return vec3(0, 0, 0);
	}

protected:
	Scene scene;
	std::vector<PointLight*> lights;
	const int max_depth =7;
};




#endif
