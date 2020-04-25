#include "Skybox.h"
#include <SOIL2.h>
#include <iostream>

Skybox::Skybox()
{
	skyShader = nullptr;
	skyMesh = nullptr;
}

void Skybox::LoadFaces(std::vector<std::string>& faceLocations)
{
	skyShader = new Shader();
	skyShader->CreateShaderFromFile("Shaders/skybox.vert", "Shaders/skybox.frag");

	uniformProjection = skyShader->GetProjectionLocation();
	uniformView = skyShader->GetViewLocation();


	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (size_t i = 0; i < 6; i++)
	{
		int width, height, bitDepth;
		unsigned char* texData = SOIL_load_image(faceLocations[i].c_str(), &width, &height, 0, SOIL_LOAD_AUTO);
		if (!texData)
		{
			std::cout << "Failed to find " << faceLocations[i].c_str() << std::endl;
			return;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		SOIL_free_image_data(texData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int skyboxIndices[] =
	{
		0,1,2,
		2,1,3,

		2,3,5,
		5,3,7,

		5,7,4,
		4,7,6,

		4,6,0,
		0,6,1,

		4,0,5,
		5,0,2,

		1,6,3,
		3,6,7,
	};

	float skyboxVertices[] =
	{
		-1.0f,1.0f,-1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		-1.0f,-1.0f,-1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		1.0f,1.0f,-1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		1.0f,-1.0f,-1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,

		-1.0f,1.0f,1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		1.0f,1.0f,1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		-1.0f,-1.0f,1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		1.0f,-1.0f,1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
	};

	skyMesh = new Mesh();
	skyMesh->CreateMesh(skyboxVertices, skyboxIndices, 88, 36);
}

Skybox::Skybox(std::vector<std::string>& faceLocations)
{
	LoadFaces(faceLocations);
}

Skybox::Skybox(Skybox& other)
{
	this->skyMesh = other.skyMesh;
	other.skyMesh = nullptr;
	this->skyShader = other.skyShader;
	other.skyShader = nullptr;

	this->textureID = other.textureID;
	this->uniformProjection = other.uniformProjection;
	this->uniformView = other.uniformView;
}

Skybox& Skybox::operator=(Skybox& other)
{
	this->skyMesh = other.skyMesh;
	other.skyMesh = nullptr;
	this->skyShader = other.skyShader;
	other.skyShader = nullptr;

	this->textureID = other.textureID;
	this->uniformProjection = other.uniformProjection;
	this->uniformView = other.uniformView;

	return *this;
}


void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));

	glDepthMask(GL_FALSE);

	skyShader->UseShader();
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	skyMesh->RenderMesh();

	glDepthMask(GL_TRUE);
}

Skybox::~Skybox()
{
	delete skyShader;
	delete skyMesh;
}
