#pragma once
#include "Light.h"
#include <vector>

class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(GLfloat shadowWidth, GLfloat shadowHeight,GLfloat near,GLfloat far, GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 position, GLfloat cons, GLfloat lin, GLfloat exp);
	void UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID, 
		GLuint positionLocation_ID,GLuint constantLocation_ID,GLuint linearLocation_ID, GLuint exponentLocation_ID);

	std::vector<glm::mat4> CalculateLightTransform();

	GLfloat GetFarPlane() const { return farPlane; }
	glm::vec3 GetPosition() const { return position; }

	~PointLight();

protected:
	glm::vec3 position;

	GLfloat constant, linear, exponent;

	GLfloat farPlane;
};

