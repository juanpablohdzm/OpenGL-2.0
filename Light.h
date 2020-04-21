#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "ShadowMap.h"

class Light
{
public:
	Light();
	Light(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue, 
		GLfloat aIntensity,GLfloat dIntensity);

	void UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID);

	ShadowMap* GetShadowMap() const { return shadowMap; }

	~Light();

protected:
	glm::vec3 colour;
	GLfloat ambientIntensity,diffuseIntensity;

	glm::mat4 lightProj;
	ShadowMap* shadowMap;
};

