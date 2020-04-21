#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 initPosition, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat rotationSpeed);
	~Camera();


	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange, GLfloat deltaTime);
	glm::mat4 CalculateViewMatrix();

	glm::vec3 GetPosition() const { return position; }
	void SetPosition(glm::vec3 val) { position = val; }
	glm::vec3 GetFront() const { return front; }
	void SetFront(glm::vec3 val) { front = val; }
	glm::vec3 GetUp() const { return up; }
	void SetUp(glm::vec3 val) { up = val; }
	glm::vec3 GetRight() const { return right; }
	void SetRight(glm::vec3 val) { right = val; }
	GLfloat GetMovementSpeed() const { return movementSpeed; }
	void SetMovementSpeed(GLfloat val) { movementSpeed = val; }
	GLfloat TurnSpeed() const { return turnSpeed; }
	void TurnSpeed(GLfloat val) { turnSpeed = val; }


private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat turnSpeed;

	void Update();
};

