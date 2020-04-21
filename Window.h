#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();

	int Initialize();

	void SetupViewportSize()
	{
		//Setup viewport size
		glViewport(0, 0, bufferWidth, bufferHeight);
	}

	void ClearWindow();

	void SwapBuffers() { glfwSwapBuffers(mainWindow); }

	GLfloat GetBufferWidth() const { return bufferWidth; }
	GLfloat GetBufferHeight() const { return bufferHeight; }
	GLfloat GetAspectRatio() const { return (GLfloat)bufferWidth / (GLfloat)bufferHeight; }

	GLfloat GetXChange();
	GLfloat GetYChange();

	bool* GetKeys() { return keys; }
	bool GetShouldClose() const { return glfwWindowShouldClose(mainWindow); }

	~Window();

private:
	GLFWwindow* mainWindow;

	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;

	bool mousedFirstMoved;

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};

