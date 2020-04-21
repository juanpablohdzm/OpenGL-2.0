#pragma once
#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include "CommonValues.h"

#include <GL/glew.h>
#include <glm/glm.hpp>


class DirectionalLight;
class PointLight;
class SpotLight;

class Shader
{

public:
	Shader();

	void CreateShader(const char* vertexCode, const char* fragmentCode);
	void CreateShaderFromFile(const char* vertexFileLocation, const char* fragmentFileLocation);

	void UseShader();
	void ClearShader();

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight* pLight, unsigned int lightCount);
	void SetDirectionalLightTransform(glm::mat4* lTransform);


	inline GLuint GetProjectionLocation() const { return uniformProjection_ID; }
	inline GLuint GetModelLocation() const { return uniformModel_ID; }
	inline GLuint GetViewLocation() const { return uniformView_ID; }
	inline GLuint GetAmbientIntensityLocation() const { return uniformDirectionalLight.uniformAmbientIntensity_ID; }
	inline GLuint GetAmbientColourLocation() const { return uniformDirectionalLight.uniformAmbientColour_ID; }
	inline GLuint GetUniformDiffuseIntensityLocation_ID() const { return uniformDirectionalLight.uniformDiffuseIntensity_ID; }
	inline GLuint GetUniformDirectionLocation_ID() const { return uniformDirectionalLight.uniformDirection_ID; }
	inline GLuint GetUniformSpecularIntensity_ID() const { return uniformSpecularIntensity_ID; }
	inline GLuint GetUniformRoughnessLocation_ID() const { return uniformRoughnessLocation_ID; }
	inline GLuint GetUniformCameraPositionLocation_ID() const { return uniformCameraPositionLocation_ID; }
	inline GLuint GetTextureLocation() const { return textureLocation; }
	inline GLuint GetNormalLocation() const { return normalLocation; }
	inline GLuint GetUseNormalLocation() const { return useNormalLocation; }
	inline GLuint GetDirectionalShadowMapLocation() const { return directionalShadowMapLocation; }
	inline GLuint GetUniformDirectionalLightTransformLocation_ID() const { return uniformDirectionalLightTransformLocation_ID; }

	~Shader();

private:
	int pointLightCount;
	int spotLightCount;
	struct
	{
		GLuint uniformAmbientColour_ID;
		GLuint uniformAmbientIntensity_ID;
		GLuint uniformDiffuseIntensity_ID;
		GLuint uniformDirection_ID;
	} uniformDirectionalLight;

	struct
	{
		GLuint uniformAmbientColour_ID;
		GLuint uniformAmbientIntensity_ID;
		GLuint uniformDiffuseIntensity_ID;

		GLuint uniformPosition_ID;
		GLuint uniformConstant_ID;
		GLuint uniformLinear_ID;
		GLuint uniformExponent_ID;
	} uniformPointLight[MAX_POINT_LIGHTS];

	struct
	{
		GLuint uniformAmbientColour_ID;
		GLuint uniformAmbientIntensity_ID;
		GLuint uniformDiffuseIntensity_ID;

		GLuint uniformPosition_ID;
		GLuint uniformConstant_ID;
		GLuint uniformLinear_ID;
		GLuint uniformExponent_ID;

		GLuint uniformDirection_ID;
		GLuint uniformEdge_ID;
	} uniformSpotLight[MAX_SPOT_LIGHTS];


	GLuint uniformPointLightCount_ID, uniformSpotLightCount_ID;
	GLuint shaderID, uniformProjection_ID, uniformModel_ID, uniformView_ID;
	GLuint uniformCameraPositionLocation_ID, uniformSpecularIntensity_ID, uniformRoughnessLocation_ID;
	GLuint uniformDirectionalLightTransformLocation_ID;

	GLuint textureLocation, normalLocation, useNormalLocation, directionalShadowMapLocation;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	std::string ReadFile(const char* fileLoc);
};

