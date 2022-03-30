// GLEW
#define GLEW_STATIC
#include <GL/glew.h> 

// WARNING: GLEW must be included before GLFW!

// GLFW
#include <GLFW/glfw3.h>

// Others
#include <iostream>
#include <fstream>
#include <string>

#include "Shader.h"

/// <summary>
/// Setting the callback for exit key.
/// </summary>
/// <param name="window"></param>
/// <param name="key"></param>
/// <param name="scancode"></param>
/// <param name="action"></param>
/// <param name="mode"></param>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 1. When a user presses the escape key, we set the WindowShouldClose propetry to ture.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main(void)
{
	// 1. Initializing GLFW.
	glfwInit();

	// 2. Setting up the hints for next glfwCreateWindow.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// 4. Creating a window and its associated context OpenGL or OpenGL ES.
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLVS", nullptr, nullptr);

	// 5. Checking if window is created.
	if (window == nullptr)
	{
		// 5.1 Outputting the message.
		std::cout << "Failed to created GFLW window and its associated context!\n";
		
		// 5.2 Frees allocated resources by GLFW, termiates the GLFW library.
		glfwTerminate();

		// 5.3 Exiting the program with error.
		return -1;
	}

	// 6. Setting up the current context for the current thread.
	glfwMakeContextCurrent(window);

	// 7. Ensuring that GLEW will be using modern techniguqes for managing OpenGL functionality.
	glewExperimental = GL_TRUE; 
	
	// 8. Initilizing GLEW.
	if (glewInit() != GLEW_OK)
	{
		// 8.1 Printing the message.
		std::cout << "Failed to initialize GLEW!\n";
		
		// 8.2 Exiting the program with error.
		return -1;
	}

	// 9. Setting up the dimensions of viewport (We want to have it for full window).
	glViewport(0, 0, 800, 600);
			// x  y  width height
	// Also OpenGL by using Viewport will be maping 2D coordinates (-1, 1) to coordinates on screen (800, 600).

	// * Setting the callback.
	glfwSetKeyCallback(window, key_callback);


	// ..:: SETTING UP AN OBJECT TO DRAW ::...

	// 2. Specify a horizontal offset via a uniform and move the triangle to the right side of the screen in the vertex shader using this offset value : .

	Shader shader("Shaders/6.7.2-Shader.vert", "Shaders/6.7.2-Shader.frag");

	GLfloat vertices[] = {
		-1.0f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// .......................................

	float offset = 0.02f;
	bool direction = true;

	// 10. Creating GAME LOOP:
	while (!glfwWindowShouldClose(window))
	{
		// 10.1 Checking if any events are triggered (like kbd) and calls the corresponding functions (which we can set via callback methods).
		glfwPollEvents();

		// 10.2 Rendering command here.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // state-setting function.
		glClear(GL_COLOR_BUFFER_BIT); // state-using function (uses the current state to retrieve the clearing color from).

		// ..:: DRAWING CODE (in GAME LOOP) ::..

		GLuint offset_LOCATION = glGetUniformLocation(shader.getProgramID(), "offset");
		
		if (offset >= 0.8f)
		{
			direction = false;
		}
		if (offset <= 0.2f)
		{
			direction=true;
		}

		if (direction)
			offset += 0.003f;
		else
			offset -= 0.003f;
		

		shader.Use();
		glUniform4f(offset_LOCATION, offset, 0.0f, 0.0f, 0.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// .....................................

		// 10.3 Swaping the color buffers.
		glfwSwapBuffers(window);
	}

	// 11. Freeing the allocated resources.
	glfwTerminate();

	// 12. Exiting the program.
	return 0;
}