#pragma once

#include <GL/glew.h>
#include "Texture.h"

class ShadowMap
{
public:
	ShadowMap();

	virtual bool Init(GLuint width, GLuint height);

	virtual void Write();

	virtual void Read(GLuint textureLocation, TextureType textureUnit);

	GLuint GetShadowWidth() const { return shadowWidth; }
	GLuint GetShadowHeight() const { return shadowHeight; }


	~ShadowMap();

protected:
	GLuint FBO, shadowMap;
	GLuint shadowWidth, shadowHeight;

};

