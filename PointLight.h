#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 position, GLfloat cons, GLfloat lin, GLfloat exp);
	void UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID, 
		GLuint positionLocation_ID,GLuint constantLocation_ID,GLuint linearLocation_ID, GLuint exponentLocation_ID);

	~PointLight();

protected:
	glm::vec3 position;

	GLfloat constant, linear, exponent;
};

