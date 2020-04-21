#include "DirectionalLight.h"
#include <glm/gtc/matrix_transform.hpp>

DirectionalLight::DirectionalLight() : Light(), direction(glm::vec3(0.0, -1.0f, 1.0f))
{
	lightProj = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 20.0f);
}

DirectionalLight::DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 dir) :
	Light(shadowWidth, shadowHeight,red,blue, green, aIntensity, dIntensity), direction(dir)
{
	lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}


void DirectionalLight::UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID, GLuint directionLocation_ID)
{
	Light::UseLight(ambientIntensityLocation_ID, ambientColourLocation_ID, diffuseIntensityLocation_ID);
	glUniform3f(directionLocation_ID, direction.x, direction.y, direction.z);
}

glm::mat4 DirectionalLight::CalculateLightTransform()
{
	return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,1.0f,0.0f));
}

DirectionalLight::~DirectionalLight()
{

}
