// #include <stdio.h>
// #include <iostream>
// #include <cmath>
// #include <string.h>
// 
// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
// 
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// 
// //Window dimensions
// const GLint WIDTH = 800, HEIGHT = 600;
// const float toRadians = 3.1416f / 180;
// 
// GLuint VAO, VBO,IBO, shader,uniformModel_ID, uniformProjection_ID;
// 
// bool direction = true;
// float triOffset = 0.0f;
// float triMaxOffset = 0.7f;
// float triIncrement = 0.005f;
// 
// float currentAngle = 0.0f;
// 
// //Vertex shader
// static const char* vShader = "#version 410   \n\
// layout (location = 0) in vec3 pos;			\n\
// uniform mat4 model;							\n\
// uniform mat4 projection;							\n\
// 											\n\
// 											\n\
// out vec4 vCol;								\n\
// 											\n\
// 											\n\
// void main()									\n\
// {											\n\
// 											\n\
// gl_Position = projection *model*vec4(pos.x, pos.y, pos.z,1.0);\n\
// vCol = vec4(clamp(pos,0.0f,1.0f),1.0f);		\n\
// 											\n\
// 											\n\
// }";
// 
// //Fragment shader
// static const char* fShader = "#version 410   \n\
// out vec4 colour;							\n\
// in vec4 vCol;								\n\
// void main()									\n\
// {											\n\
// 	colour = vCol;							\n\
// 											\n\
// }";
// 
// void CreateTriangle()
// {
// 	unsigned int indices[] =
// 	{
// 		0,3,1,
// 		1,3,2,
// 		2,3,0,
// 		0,1,2
// 	};
// 
// 	GLfloat vertices[] = {
// 		-1.0f,-1.0f,0.0f, 
// 		0.0f, -1.0f,1.0f,
// 		1.0f,-1.0f,0.0f,
// 		0.0f,1.0f,0.0f
// 	};
// 
// 	glGenVertexArrays(1, &VAO);//Create an ID to get the array in the graphics card
// 		glBindVertexArray(VAO);
// 
// 		glGenBuffers(1, &IBO);
// 		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
// 		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
// 
// 			glGenBuffers(1, &VBO);
// 			glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 
// 				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
// 
// 				glEnableVertexAttribArray(0);
// 
// 			glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind array buffer
// 
// 
// 		glBindVertexArray(0); //Unbind vao
// 
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
// 		
// }
// 
// void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
// {
// 	GLuint theShader = glCreateShader(shaderType);
// 
// 	const GLchar* theCode = shaderCode;
// 
// 	GLint codeLength = strlen(shaderCode);
// 
// 	glShaderSource(theShader, 1, &theCode, &codeLength);
// 	glCompileShader(theShader);
// 
// 	GLint result = 0;
// 	GLchar eLog[1024] = { 0 };
// 
// 
// 	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
// 	if (!result)
// 	{
// 		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
// 		std::cout << "Error compiling the "<< shaderType << "program " << eLog << std::endl;
// 		return;
// 	}
// 
// 	glAttachShader(theProgram, theShader);
// 
// }
// 
// void CompileShaders()
// {
// 	shader = glCreateProgram();
// 
// 	if (!shader)
// 	{
// 		std::cout << "Error creating shader program" << std::endl;
// 		return;
// 	}
// 
// 	AddShader(shader, vShader, GL_VERTEX_SHADER);
// 	AddShader(shader, fShader, GL_FRAGMENT_SHADER);
// 
// 	GLint result = 0;
// 	GLchar eLog[1024] = { 0 };
// 
// 	glLinkProgram(shader);
// 	glGetProgramiv(shader, GL_LINK_STATUS, &result);
// 	if (!result)
// 	{
// 		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
// 		std::cout << "Error linking program " << eLog << std::endl;
// 		return;
// 	}
// 
// 	glValidateProgram(shader);
// 	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
// 	if (!result)
// 	{
// 		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
// 		std::cout << "Error validating program " << eLog << std::endl;
// 		return;
// 	}
// 
// 	uniformModel_ID = glGetUniformLocation(shader, "model");
// 	uniformProjection_ID = glGetUniformLocation(shader, "projection");
// }
// 
// int main()
// {
// 	//Initialize GLFW
// 	if (!glfwInit())
// 	{
// 		std::cout << "GLFW Initialization error" << std::endl;
// 		glfwTerminate();
// 		return 1;
// 	}
// 
// 	//Setup GLFW Window properties
// 	//OpenGL version 
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
// 
// 	//Core profile = No backwards compatibility
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// 
// 	//Allow forward compatibility
// 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
// 
// 	//Create window
// 	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH,HEIGHT,"Main Window", NULL, NULL);
// 	if (!mainWindow)
// 	{
// 		std::cout << "GLFW window creation error" << std::endl;
// 		glfwTerminate();
// 		return 1;
// 	}
// 
// 
// 	//Set context for GLEW to use, what window is the important one
// 	glfwMakeContextCurrent(mainWindow);
// 
// 	//Allow modern extension features
// 	glewExperimental = GL_TRUE;
// 
// 	if (glewInit() != GLEW_OK)
// 	{
// 		std::cout << "GLEW Initialization error" << std::endl;
// 		glfwDestroyWindow(mainWindow);
// 		glfwTerminate();
// 		return 1;
// 	}
// 
// 	glEnable(GL_DEPTH_TEST);
// 
// 	// Get buffer size information
// 	int bufferWidth, bufferHeight;
// 	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
// 
// 	//Setup viewport size
// 	glViewport(0, 0, bufferWidth, bufferHeight);
// 
// 	CreateTriangle();
// 	CompileShaders();
// 
// 	glm::mat4 proj = glm::perspective(45.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);
// 	
// 
// 	//loop until window closed
// 	while (!glfwWindowShouldClose(mainWindow))
// 	{
// 		//Get + Handle user input events
// 		glfwPollEvents();
// 
// 		triOffset += direction?  triIncrement : -triIncrement;
// 
// 		if (abs(triOffset) >= triMaxOffset)
// 			direction = !direction;
// 
// 		currentAngle += 0.3f;
// 		if (currentAngle >= 360) currentAngle -= 360.0f;
// 
// 		//Clear window
// 		glClearColor(0.0f, 0, 0, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
// 		glUseProgram(shader);
// 
// 		glm::mat4 model(1.0f);
// 		model = glm::translate(model, glm::vec3(0.0f, triOffset, -2.5f));
// 		model = glm::rotate(model, glm::radians(currentAngle), glm::vec3(0.0f, 1.0f, 0.0f));
// 		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
// 
// 			glUniformMatrix4fv(uniformModel_ID, 1, GL_FALSE, glm::value_ptr(model));
// 			glUniformMatrix4fv(uniformProjection_ID,1,GL_FALSE, glm::value_ptr(proj));
// 
// 				glBindVertexArray(VAO);
// 				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
// 
// 				glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,0);
// 
// 				glBindVertexArray(0);
// 				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
// 
// 		glUseProgram(0);
// 
// 		glfwSwapBuffers(mainWindow);
// 	}
// 
// 	glfwDestroyWindow(mainWindow);
// 	glfwTerminate();
// 
// 	return 0;
// }