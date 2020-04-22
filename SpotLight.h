#pragma once
#include "PointLight.h"
class SpotLight :
	public PointLight
{
public:
	SpotLight();
	SpotLight(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat near, GLfloat far, GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 position,glm::vec3 dir, GLfloat edge, GLfloat cons, GLfloat lin, GLfloat exp);
	void UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID,
		GLuint positionLocation_ID,  GLuint directionalLocation_ID, GLuint constantLocation_ID, GLuint linearLocation_ID, GLuint exponentLocation_ID, GLuint edgeLocation_ID);
	~SpotLight();

private:
	glm::vec3 direction;
	GLfloat edge, procEdge;
};

