#include "PointLight.h"

PointLight::PointLight() : Light(),constant(1.0f),linear(0.0f),exponent(0.0f),position(glm::vec3(0.0f,0.0f,0.0f))
{

}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
    glm::vec3 position, GLfloat cons, GLfloat lin, GLfloat exp): Light(1024,1024,red,green,blue,aIntensity,dIntensity), position(position),constant(cons),linear(lin), exponent(exp)
{

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

PointLight::~PointLight()
{

}
