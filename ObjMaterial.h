// Code from GEL (http://www.imm.dtu.dk/GEL/)
// Copyright (c) DTU Informatics 2011
#ifndef OBJMATERIAL_H
#define OBJMATERIAL_H
//#include"Utility.h"
#include <string>
enum MaterialType {
	kDiffuse, kReflective, kRefractive,Light
};
struct ObjMaterial
{
	/// Name of material
	//std::string name;
	MaterialType type;
	/// Diffuse reflection
	glm::vec3 diffuse;

	/// Ambient reflection
	glm::vec3 ambient;

	/// Specular reflection
	glm::vec3 specular;

	/// Specular exponent
	float shininess;

	/// Index of refraction
	float ior;

	/// Transmission filter
	glm::vec3 transmission;

	/** Illumination model
		  0 - Color
		  1 - Color and ambient
		  2 - Color and ambient and highlight
		  3 - Reflection
		  4 - Reflection and refraction
		Refer to the MTL format specification for more models.
		Only numbers from 0 to 10 have a specific meaning. */
	int illum;

	bool has_texture;
	std::string tex_path, tex_name;
	int tex_id;

	ObjMaterial() : type(kDiffuse),
		tex_path(""), tex_name(""), tex_id(-1), has_texture(false)
	{
		ior = 1.5f;
		shininess = 0.0f;
		diffuse[0] = 0.8f;
		diffuse[1] = 0.8f;
		diffuse[2] = 0.8f;
		//diffuse[3] = 1.0f;
		ambient[0] = 0.2f;
		ambient[1] = 0.2f;
		ambient[2] = 0.2f;
		//ambient[3] = 1.0f;
		specular[0] = 0.0f;
		specular[1] = 0.0f;
		specular[2] = 0.0f;
	//	specular[3] = 1.0f;
		transmission[0] = 0.0f;
		transmission[1] = 0.0f;
		transmission[2] = 0.0f;
		illum = 2;
	}
};

#endif // OBJMATERIAL_H

