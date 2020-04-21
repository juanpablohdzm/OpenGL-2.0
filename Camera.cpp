#include "Camera.h"
#include <cmath>
#include <iostream>

Camera::Camera(glm::vec3 initPosition, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat rotationSpeed) :
	position(initPosition), up(up), yaw(yaw), pitch(pitch),
	front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(moveSpeed),
	turnSpeed(rotationSpeed), right(glm::vec3(-1.0f, 0.0f, 0.0f))
{
	Update();
}

Camera::Camera()
{

}

void Camera::Update()
{
	front.z = -std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	front.y = std::sin(glm::radians(pitch));
	front.x = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front,glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right ,front));


}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{

	if (keys[GLFW_KEY_UP])
	{
		position += front * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_DOWN])
	{
		position -= front * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_RIGHT])
	{
		position += right * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_LEFT])
	{
		position -= right * movementSpeed * deltaTime;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange, GLfloat deltaTime)
{
	pitch += yChange * turnSpeed * deltaTime;
	yaw += xChange * turnSpeed * deltaTime;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	Update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

Camera::~Camera()
{

}
