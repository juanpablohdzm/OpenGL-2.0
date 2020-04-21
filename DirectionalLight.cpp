#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light(), direction(glm::vec3(0.0, -1.0f, 1.0f))
{}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 dir) : 
	Light(red,blue, green, aIntensity, dIntensity), direction(dir)
{}


void DirectionalLight::UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID, GLuint directionLocation_ID)
{
	Light::UseLight(ambientIntensityLocation_ID, ambientColourLocation_ID, diffuseIntensityLocation_ID);
	glUniform3f(directionLocation_ID, direction.x, direction.y, direction.z);
}

DirectionalLight::~DirectionalLight()
{

}
