#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,GLfloat dIntensity);

	void UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID);


	~Light();

protected:
	glm::vec3 colour;
	GLfloat ambientIntensity,diffuseIntensity;
};

