#include "Material.h"
#include <iostream>

Material::Material() : specularIntensity(0), roughness(0)
{

}

Material::Material(GLfloat sIntensity, GLfloat roughness): specularIntensity(sIntensity), roughness(roughness)
{

}

void Material::UseMaterial(GLuint uniformSpecularIntensityLocation_ID, GLuint unifomRoughnessLocation_ID)
{
	glUniform1f(uniformSpecularIntensityLocation_ID, specularIntensity);
	glUniform1f(unifomRoughnessLocation_ID, roughness);
}

Material::~Material()
{

}
