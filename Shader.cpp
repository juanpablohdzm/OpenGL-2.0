#include "Shader.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

Shader::Shader() : shaderID(0), uniformModel_ID(0), uniformProjection_ID(0),pointLightCount(0),spotLightCount(0)
{

}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode = shaderCode;

	GLint codeLength = strlen(shaderCode);

	glShaderSource(theShader, 1, &theCode, &codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };


	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling the " << shaderType << "program " << eLog << std::endl;
		return;
	}

	glAttachShader(theProgram, theShader);

}

void Shader::CompileProgram()
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program " << eLog << std::endl;
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program " << eLog << std::endl;
		return;
	}

	uniformModel_ID = glGetUniformLocation(shaderID, "model");
	uniformProjection_ID = glGetUniformLocation(shaderID, "projection");
	uniformView_ID = glGetUniformLocation(shaderID, "view");
	uniformCameraPositionLocation_ID = glGetUniformLocation(shaderID, "eyePosition");

	uniformDirectionalLight.uniformAmbientColour_ID = glGetUniformLocation(shaderID, "directionalLight.base.colour");
	uniformDirectionalLight.uniformAmbientIntensity_ID = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDirection_ID = glGetUniformLocation(shaderID, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity_ID = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");

	uniformPointLightCount_ID = glGetUniformLocation(shaderID, "pointLightCount");
	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char name[100] = { '\0' };
		snprintf(name, sizeof(name), "pointLights[%d].base.colour", i);
		uniformPointLight[i].uniformAmbientColour_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLight[i].uniformAmbientIntensity_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLight[i].uniformDiffuseIntensity_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "pointLights[%d].position", i);
		uniformPointLight[i].uniformPosition_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "pointLights[%d].constant", i);
		uniformPointLight[i].uniformConstant_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "pointLights[%d].linear", i);
		uniformPointLight[i].uniformLinear_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "pointLights[%d].exponent", i);
		uniformPointLight[i].uniformExponent_ID = glGetUniformLocation(shaderID, name);
	}

	uniformSpotLightCount_ID = glGetUniformLocation(shaderID, "spotLightCount");
	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char name[100] = { '\0' };
		snprintf(name, sizeof(name), "spotLights[%d].base.base.colour", i);
		uniformSpotLight[i].uniformAmbientColour_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "spotLights[%d].base.base.ambientIntensity", i);
		uniformSpotLight[i].uniformAmbientIntensity_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "spotLights[%d].base.base.diffuseIntensity", i);
		uniformSpotLight[i].uniformDiffuseIntensity_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "spotLights[%d].base.position", i);
		uniformSpotLight[i].uniformPosition_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "spotLights[%d].base.constant", i);
		uniformSpotLight[i].uniformConstant_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "spotLights[%d].base.linear", i);
		uniformSpotLight[i].uniformLinear_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "spotLights[%d].base.exponent", i);
		uniformSpotLight[i].uniformExponent_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "spotLights[%d].direction", i);
		uniformSpotLight[i].uniformDirection_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "spotLights[%d].edge", i);
		uniformSpotLight[i].uniformEdge_ID = glGetUniformLocation(shaderID, name);
	}


	uniformSpecularIntensity_ID = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformRoughnessLocation_ID = glGetUniformLocation(shaderID, "material.roughness");

	textureLocation = glGetUniformLocation(shaderID, "theTexture");
	normalLocation = glGetUniformLocation(shaderID, "normalTexture");
	useNormalLocation = glGetUniformLocation(shaderID, "useNormalTexture");

	directionalShadowMapLocation = glGetUniformLocation(shaderID, "directionalShadowMap");

	uniformOmniLightPosLocation_ID = glGetUniformLocation(shaderID, "lightPos");
	uniformFarPlaneLocation_ID = glGetUniformLocation(shaderID, "farPlane");


	uniformDirectionalLightTransformLocation_ID = glGetUniformLocation(shaderID, "directionalLightTransform");

	for (size_t i = 0; i < 6; i++)
	{
		char name[100] = { '\0' };
		snprintf(name, sizeof(name), "lightMatrices[%d]", i);
		uniformlightMatrices[i] = glGetUniformLocation(shaderID, name);
	}

	for (size_t i = 0; i < 3; i++)
	{
		char name[100] = { '\0' };
		snprintf(name, sizeof(name), "omniShadowMaps[%d].shadowMap", i);
		uniformOmniShadowMap[i].uniformShadowMap_ID = glGetUniformLocation(shaderID, name);

		snprintf(name, sizeof(name), "omniShadowMaps[%d].farPlane", i);
		uniformOmniShadowMap[i].uniformFarPlane_ID = glGetUniformLocation(shaderID, name);
	}

	timeLocation = glGetUniformLocation(shaderID, "_time");
	bUseTimeLocation = glGetUniformLocation(shaderID, "bUseTime");
}



void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		std::cout << "Error creating shader program" << std::endl;
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	CompileProgram();
}

void Shader::CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		std::cout << "Error creating shader program" << std::endl;
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, geometryCode, GL_GEOMETRY_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	CompileProgram();
}

void Shader::CreateShader(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLoc)
{

	std::ifstream fileStream(fileLoc, std::ios::in);

	if (!fileStream.is_open())
	{
		std::cout << "Failed to read " << fileLoc << std::endl;
		return "";
	}

	return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
}

void Shader::CreateShaderFromFile(const char* vertexFileLocation, const char* fragmentFileLocation)
{
	CompileShader(ReadFile(vertexFileLocation).c_str(), ReadFile(fragmentFileLocation).c_str());
}

void Shader::CreateShaderFromFile(const char* vertexFileLocation, const char* geometryFileLocation, const char* fragmentFileLocation)
{
	CompileShader(ReadFile(vertexFileLocation).c_str(),ReadFile(geometryFileLocation).c_str(), ReadFile(fragmentFileLocation).c_str());
}

void Shader::UseShader()
{
	glUseProgram(shaderID);	
}

void Shader::ClearShader()
{
	if (shaderID)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel_ID = 0;
	uniformProjection_ID = 0;
}

void Shader::SetDirectionalLight(DirectionalLight* dLight)
{
	dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity_ID, uniformDirectionalLight.uniformAmbientColour_ID,
		uniformDirectionalLight.uniformDiffuseIntensity_ID, uniformDirectionalLight.uniformDirection_ID);
}

void Shader::SetPointLights(PointLight* pLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset)
{
	if (lightCount > MAX_POINT_LIGHTS) 
		lightCount = MAX_POINT_LIGHTS;
	
	glUniform1i(uniformPointLightCount_ID, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity_ID, uniformPointLight[i].uniformAmbientColour_ID, uniformPointLight[i].uniformDiffuseIntensity_ID,
			uniformPointLight[i].uniformPosition_ID, uniformPointLight[i].uniformConstant_ID, uniformPointLight[i].uniformLinear_ID, uniformPointLight[i].uniformExponent_ID);

		glUniform1i(uniformOmniShadowMap[i + offset].uniformShadowMap_ID, textureUnit + i);
		glUniform1f(uniformOmniShadowMap[i + offset].uniformFarPlane_ID, pLight[i].GetFarPlane());
		pLight[i].GetShadowMap()->Read(uniformOmniShadowMap[i + offset].uniformShadowMap_ID, textureUnit + i);
	}
}

void Shader::SetSpotLights(SpotLight* pLight, unsigned int lightCount,unsigned int textureUnit, unsigned int offset)
{
	if (lightCount > MAX_SPOT_LIGHTS)
		lightCount = MAX_SPOT_LIGHTS;

	glUniform1i(uniformSpotLightCount_ID, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].UseLight(uniformSpotLight[i].uniformAmbientIntensity_ID, uniformSpotLight[i].uniformAmbientColour_ID, uniformSpotLight[i].uniformDiffuseIntensity_ID,
			uniformSpotLight[i].uniformPosition_ID,uniformSpotLight[i].uniformDirection_ID, uniformSpotLight[i].uniformConstant_ID, uniformSpotLight[i].uniformLinear_ID, uniformSpotLight[i].uniformExponent_ID, uniformSpotLight[i].uniformEdge_ID);

		glUniform1i(uniformOmniShadowMap[i + offset].uniformShadowMap_ID, textureUnit + i);
		glUniform1f(uniformOmniShadowMap[i + offset].uniformFarPlane_ID, pLight[i].GetFarPlane());
		pLight[i].GetShadowMap()->Read(uniformOmniShadowMap[i + offset].uniformShadowMap_ID, textureUnit + i);
	}
}

void Shader::SetDirectionalLightTransform(glm::mat4* lTransform)
{
	glUniformMatrix4fv(uniformDirectionalLightTransformLocation_ID, 1, GL_FALSE, glm::value_ptr(*lTransform));
}

void Shader::SetUniformlightMatrices(std::vector<glm::mat4> lightMatrices)
{
	for (size_t i = 0; i < 6; i++)
	{
		glUniformMatrix4fv(uniformlightMatrices[i], 1, GL_FALSE, glm::value_ptr(lightMatrices[i]));
	}
}

Shader::~Shader()
{
	ClearShader();
}


