#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Model.h"
#include "CommonValues.h"
#include "Material.h"

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera camera;

Model cat;

Texture brickTexture;
Texture snowTexture;
Texture whiteTexture;
Texture brickNormalTexture;
Texture snowNormalTexture;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

Material shinyMaterial;
Material dullMaterial;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

//Vertex shader
static const char* vShader = "Shaders/shader.vert";

//Fragment shader
static const char* fShader = "Shaders/shader.frag";

void CalculateAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, unsigned int vLength, 
	unsigned int normalOffset)
{
	for (size_t i = 0; i< indiceCount; i+=3)
	{
		unsigned int in0 = indices[i]*vLength;
		unsigned int in1 = indices[i+1]*vLength;
		unsigned int in2 = indices[i+2]*vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal=glm::cross(v2, v1);
		normal = glm::normalize(normal);

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += normal.x;
		vertices[in0+1] += normal.y;
		vertices[in0+2] += normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}

	for (size_t i=0; i<verticeCount/vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x;
		vertices[nOffset+1] = vec.y;
		vertices[nOffset+2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int indices[] =
	{
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};

	GLfloat vertices[] = {
		-1.0f,-1.0f,0.0f,	0.0f,0.0f,	0.0f,0.0f,0.0f,
		0.0f, -1.0f,1.0f,	0.5f,0.0f,	0.0f,0.0f,0.0f,
		1.0f,-1.0f,0.0f,	1.0f,0.0f,	0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,		0.5f,1.0f,	0.0f,0.0f,0.0f
	};

	unsigned int floorIndices[] = {
		2,1,0,
		2,3,1
	};

	GLfloat floorVertices[] = {
		-10.0f,0.0f,-10.0f, 0.0f,0.0f, 0.0f,1.0f,0.0f,
		10.0f,0.0f,-10.0f, 10.0f,0.0f, 0.0f,1.0f,0.0f,
		-10.0f,0.0f,10.0f, 0.0f,10.0f, 0.0f,1.0f,0.0f,
		10.0f,0.0f,10.0f, 10.0f,10.0f, 0.0f,1.0f,0.0f
	};

	CalculateAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj = new Mesh();
	obj->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj);

	obj = new Mesh();
	obj->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj);

	obj = new Mesh();
	obj->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj);
		
}

void DestroyObjects()
{
	for (Mesh* p : meshList)
	{
		delete p;
		p = nullptr;
	}
}

void CreateShaders()
{
	Shader* shader = new Shader();
	shader->CreateShaderFromFile(vShader, fShader);
	shaderList.push_back(shader);
}

void DestroyShaders()
{
	for (Shader* p : shaderList)
	{
		delete p;
		p = nullptr;
	}
}

int main()
{
	mainWindow.Initialize();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 3.0f);
	brickTexture = Texture("Textures/brick.jpg");
	brickTexture.LoadTexture();
	brickNormalTexture = Texture("Textures/brickNormal.jpg");
	brickNormalTexture.LoadTexture();
	snowTexture = Texture("Textures/snow.jpg");
	snowTexture.LoadTexture();
	snowNormalTexture = Texture("Textures/snowNormal.jpg");
	snowNormalTexture.LoadTexture();
	whiteTexture = Texture("Textures/white.jpg");
	whiteTexture.LoadTexture();

	shinyMaterial = Material(1.0f, 32);
	dullMaterial = Material(0.3f, 8);

	cat = Model();
	cat.LoadModel("Models/Cat.obj");

	mainLight = DirectionalLight(1.0f,1.0f,1.0f,0.4f,0.2f, glm::vec3(0.0f, 0.0f, -1.0f));
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.1f, 0.6f,
		glm::vec3(-3.0f, 0.0f, 0.0f),
		0.3f, 0.2f, 0.1);
	pointLights[1] = PointLight(0.0f, 0.0f, 1.0f,
		0.1f, 0.6f,
		glm::vec3(3.0f, 0.0f, 0.0f),
		0.3f, 0.2f, 0.1);
	unsigned int pointLightCount = 2;

	spotLights[0] = SpotLight(0.0f, 1.0f, 0.0f,
		0.6f, 1.0f,
		glm::vec3(0.0f, -1.0f, 2.0f),
		glm::vec3(0.0f,-1.0f,-4.0f), 30.0f,
		0.3f, 0.2f, 0.1);

	unsigned int spotLightCount = 0;

	GLuint uniformProjection_ID=0, uniformModel_ID = 0, uniformView_ID=0,uniformSpecularIntensity_ID =0,uniformRoughness_ID=0,uniformCameraLocation_ID=0;
	glm::mat4 proj = glm::perspective(45.0f, mainWindow.GetAspectRatio(), 0.1f, 100.0f);

	//loop until window closed
	while (!mainWindow.GetShouldClose())
	{
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//Get + Handle user input events
		glfwPollEvents();

		camera.KeyControl(mainWindow.GetKeys(),deltaTime);
		camera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange(), deltaTime);

		//Clear window
		mainWindow.ClearWindow();

		shaderList[0]->UseShader();
		uniformModel_ID = shaderList[0]->GetModelLocation();
		uniformProjection_ID = shaderList[0]->GetProjectionLocation();
		uniformView_ID = shaderList[0]->GetViewLocation();
		uniformSpecularIntensity_ID = shaderList[0]->GetUniformSpecularIntensity_ID();
		uniformRoughness_ID = shaderList[0]->GetUniformRoughnessLocation_ID();
		uniformCameraLocation_ID = shaderList[0]->GetUniformCameraPositionLocation_ID();

		glm::vec3 camLocation = camera.GetPosition();
		glUniform3f(uniformCameraLocation_ID, camLocation.x, camLocation.y, camLocation.z);
		glUniformMatrix4fv(uniformProjection_ID,1,GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(uniformView_ID,1,GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

// 		glm::mat4 model(1.0f);
// 		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
// 		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
// 		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
// 		glUniformMatrix4fv(uniformModel_ID, 1, GL_FALSE, glm::value_ptr(model));
// 		snowTexture.UseTexture(TextureType::DIFFUSE,true, shaderList[0]->GetTextureLocation(),shaderList[0]->GetUseNormalLocation());
// 		snowNormalTexture.UseTexture(TextureType::NORMAL, true, shaderList[0]->GetNormalLocation(), shaderList[0]->GetUseNormalLocation());
// 		dullMaterial.UseMaterial(uniformSpecularIntensity_ID, uniformRoughness_ID);
// 		meshList[0]->RenderMesh();

		glm::mat4 model1(1.0f);
		model1 = glm::translate(model1, glm::vec3(0.0f, 1.0f, -2.5f));
		model1 = glm::rotate(model1, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model1 = glm::scale(model1, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel_ID, 1, GL_FALSE, glm::value_ptr(model1));
		brickTexture.UseTexture(TextureType::DIFFUSE,true, shaderList[0]->GetTextureLocation(), shaderList[0]->GetUseNormalLocation());
		brickNormalTexture.UseTexture(TextureType::NORMAL,true, shaderList[0]->GetNormalLocation(), shaderList[0]->GetUseNormalLocation());
		shinyMaterial.UseMaterial(uniformSpecularIntensity_ID, uniformRoughness_ID);
		meshList[1]->RenderMesh();

		glm::mat4 model2(1.0f);
		model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel_ID, 1, GL_FALSE, glm::value_ptr(model2));
		whiteTexture.UseTexture(TextureType::DIFFUSE,false,shaderList[0]->GetTextureLocation(), shaderList[0]->GetUseNormalLocation());		
		shinyMaterial.UseMaterial(uniformSpecularIntensity_ID, uniformRoughness_ID);
		meshList[2]->RenderMesh();

		glm::mat4 model3(1.0f);
		model3 = glm::scale(model3, glm::vec3(0.05f, 0.05f, 0.05f));
		model3 = glm::rotate(model3, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model3 = glm::translate(model3, glm::vec3(0.0f, 0.0f, -20.5f));
		glUniformMatrix4fv(uniformModel_ID, 1, GL_FALSE, glm::value_ptr(model3));
		shinyMaterial.UseMaterial(uniformSpecularIntensity_ID, uniformRoughness_ID);
		cat.RenderModel(shaderList[0]->GetTextureLocation(), shaderList[0]->GetNormalLocation(), shaderList[0]->GetUseNormalLocation());

		shaderList[0]->SetDirectionalLight(&mainLight);
		shaderList[0]->SetPointLights(pointLights, pointLightCount);
		shaderList[0]->SetSpotLights(spotLights, spotLightCount);

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	DestroyShaders();
	DestroyObjects();

	return 0;
}