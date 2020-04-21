#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	DirectionalLight();

	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 dir);
	void UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID,  GLuint diffuseIntensityLocation_ID, GLuint directionLocation_ID);

	~DirectionalLight();


private:
	glm::vec3 direction;
};

