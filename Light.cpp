#include "Light.h"
#include "ShadowMap.h"

Light::Light() : colour(glm::vec3(1.0f,1.0f,1.0f)),ambientIntensity(1.0f),diffuseIntensity(1.0f)
{

}

Light::Light(GLfloat shadowWidth,GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,  GLfloat dIntensity) : 
	colour(glm::vec3(red, green, blue)), ambientIntensity(aIntensity),diffuseIntensity(dIntensity)
{
	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
}

void Light::UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID)
{
	glUniform3f(ambientColourLocation_ID, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation_ID, ambientIntensity);
	glUniform1f(diffuseIntensityLocation_ID, diffuseIntensity);
}

Light::~Light()
{

}
