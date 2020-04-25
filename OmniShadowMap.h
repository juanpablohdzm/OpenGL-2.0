#pragma once
#include "ShadowMap.h"
class OmniShadowMap :
	public ShadowMap
{
public:
	OmniShadowMap();

	bool Init(GLuint width, GLuint height) override;


	void Write() override;


	void Read(GLuint textureLocation, TextureType textureUnit) override;
	void Read(GLuint textureLocation, GLuint textureUnit) override;

	~OmniShadowMap();


private:

};

