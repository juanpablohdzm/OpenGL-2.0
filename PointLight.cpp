#include "PointLight.h"
#include "OmniShadowMap.h"
#include <glm/gtc/matrix_transform.hpp>

PointLight::PointLight() : Light(),constant(1.0f),linear(0.0f),exponent(0.0f),position(glm::vec3(0.0f,0.0f,0.0f))
{

}

PointLight::PointLight(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat near, GLfloat far, GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
    glm::vec3 position, GLfloat cons, GLfloat lin, GLfloat exp) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity), position(position), constant(cons), linear(lin), exponent(exp), farPlane(far)
{
    float aspect = shadowWidth / shadowHeight;
    lightProj = glm::perspective(glm::radians(90.0f),aspect,near,far);

    shadowMap = new OmniShadowMap();
    shadowMap->Init(shadowWidth, shadowHeight);
}

void PointLight::UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID, 
    GLuint positionLocation_ID, GLuint constantLocation_ID, GLuint linearLocation_ID, GLuint exponentLocation_ID)
{
    Light::UseLight(ambientIntensityLocation_ID, ambientColourLocation_ID, diffuseIntensityLocation_ID);
    glUniform3f(positionLocation_ID, position.x, position.y, position.z);
    glUniform1f(constantLocation_ID, constant);
    glUniform1f(linearLocation_ID, linear);
    glUniform1f(exponentLocation_ID, exponent);
}

std::vector<glm::mat4> PointLight::CalculateLightTransform()
{
    std::vector<glm::mat4> lightMatrices;
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f)));

    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f,0.0f,-1.0f)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f),glm::vec3(0.0f,0.0f,1.0f)));

    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f),glm::vec3(0.0f,1.0f,0.0f)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f),glm::vec3(0.0f,1.0f,0.0f)));

    return lightMatrices;
}

PointLight::~PointLight()
{

}
