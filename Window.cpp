#include "Window.h"

Window::Window() : bufferHeight(0),bufferWidth(0),
					mainWindow(nullptr), lastX(0),lastY(0),xChange(0),yChange(0), mousedFirstMoved(false)
{
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

int Window::Initialize()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW Initialization error" << std::endl;
		glfwTerminate();
		return 1;
	}

	//Setup GLFW Window properties
	//OpenGL version 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	//Core profile = No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	//Create window
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	mainWindow = glfwCreateWindow(mode->width, mode->height, "Main Window", monitor, NULL);
	if (!mainWindow)
	{
		std::cout << "GLFW window creation error" << std::endl;
		glfwTerminate();
		return 1;
	}


	//Set context for GLEW to use, what window is the important one
	glfwMakeContextCurrent(mainWindow);

	//Handle key + Mouse input
	CreateCallbacks();
	glfwSetInputMode(mainWindow,GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Initialization error" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	//Setup what window will handle the callbacks
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::CreateCallbacks()
{
	glfwSetKeyCallback(mainWindow, HandleKeys);
	glfwSetCursorPosCallback(mainWindow, HandleMouse);
}

void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else
			if (action == GLFW_RELEASE)
			{
				theWindow->keys[key] = false;
			}
	}
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (!theWindow->mousedFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mousedFirstMoved = true;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = -yPos + theWindow->lastY;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

}

void Window::ClearWindow()
{
	glClearColor(0.0f, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLfloat Window::GetXChange() 
{
	GLfloat change = xChange;
	xChange = 0;
	return change;
}

GLfloat Window::GetYChange()
{
	GLfloat change = yChange;
	yChange = 0;
	return change;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

