#include "Texture.h"
#include <SOIL2.h>
#include <iostream>

Texture::Texture() : width(0), height(0), bitDepth(0), textureID(0), fileLocation(nullptr)
{

}

Texture::Texture(const char* fileLocation): width(0), height(0), bitDepth(0), textureID(0), fileLocation(fileLocation)
{
}

bool Texture::LoadTexture()
{
	unsigned char* texData = SOIL_load_image(fileLocation, &width, &height, 0, SOIL_LOAD_AUTO);
	if (!texData)
	{
		std::cout << "Failed to find " << fileLocation << std::endl;
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,0);

	SOIL_free_image_data(texData);

	return true;
}

bool Texture::LoadTextureA()
{
	unsigned char* texData = SOIL_load_image(fileLocation, &width, &height, 0, SOIL_LOAD_AUTO);
	if (!texData)
	{
		std::cout << "Failed to find " << fileLocation << std::endl;
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	SOIL_free_image_data(texData);

	return true;
}

void Texture::UseTexture(TextureType type, bool useNormalTexture,GLuint textureLocation, GLuint useNormalLocation)
{
	glUniform1i(useNormalLocation, useNormalTexture);

	glUniform1i(textureLocation, (int)type);
	glActiveTexture(GL_TEXTURE0 + (int)type);

	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	fileLocation = "";
}

Texture::~Texture()
{
	ClearTexture();
}
