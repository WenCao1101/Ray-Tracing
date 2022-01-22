#include "Light.h"
//#include "Ray.h"
#include"Shape.h"
//#include"ObjMaterial.h"

namespace
{
	const float M_1_PIf = 0.31830988618379067154f;
}

bool PointLight::sample(const vec3& position) const {
	/*auto dir = normalize(pos - position);
	Ray ss(ray_from(position));
	light=dot(dir,ss.)*ss.get_hit_material()*/
	return true;
};
vec3 AreaLight::get_emission_obj(int triangle_id) const
{
	const ObjMaterial* mat = &mesh->triangles[triangle_id].mat_ptr;
	if (mat == mat || mat != NULL)
		return mat ? mat->ambient : vec3(0.0f);
	else
		return vec3(0.0f);

};

bool AreaLight::sample(const vec3& position) const {


	return true;

}