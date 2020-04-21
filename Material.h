#pragma once
#include <GL/glew.h>

class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat roughness);
	
	void UseMaterial(GLuint uniformSpecularIntensityLocation_ID, GLuint unifomRoughnessLocation_ID);
	
	~Material();



private:
	GLfloat specularIntensity;
	GLfloat roughness;
	
};

