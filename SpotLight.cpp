#include "SpotLight.h"

SpotLight::SpotLight() : PointLight(), direction(glm::vec3(0.0f,0.0f,0.0f)),edge(0.0f), procEdge(1.0f)
{

}



SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 position,
    glm::vec3 dir, GLfloat edge,  GLfloat cons, GLfloat lin, GLfloat exp) : PointLight(red,green,blue,aIntensity,dIntensity,position,cons,lin,exp),direction(dir), edge(edge)
{
    procEdge = std::cosf(glm::radians(edge));
}



void SpotLight::UseLight(GLuint ambientIntensityLocation_ID, GLuint ambientColourLocation_ID, GLuint diffuseIntensityLocation_ID, GLuint positionLocation_ID, GLuint directionalLocation_ID, GLuint constantLocation_ID, GLuint linearLocation_ID, GLuint exponentLocation_ID, GLuint edgeLocation_ID)
{
    PointLight::UseLight(ambientIntensityLocation_ID, ambientColourLocation_ID, diffuseIntensityLocation_ID, positionLocation_ID, constantLocation_ID, linearLocation_ID, exponentLocation_ID);
    glUniform3f(directionalLocation_ID, direction.x, direction.y, direction.z);
    glUniform1f(edgeLocation_ID, procEdge);

}

SpotLight::~SpotLight()
{

}
