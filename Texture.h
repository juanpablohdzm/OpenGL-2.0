#pragma once
#include <GL/glew.h>

enum class TextureType {DIFFUSE=0,NORMAL,DIRECTIONAL_SHADOWMAP};

class Texture
{
public:
	Texture();
	Texture(const char* fileLocation);

	bool LoadTexture();
	bool LoadTextureA();
	void UseTexture(TextureType type, bool useNormalTexture = false ,GLuint textureLocation =0, GLuint useNormalLocation=0);
	void ClearTexture();

	~Texture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLocation;
};

