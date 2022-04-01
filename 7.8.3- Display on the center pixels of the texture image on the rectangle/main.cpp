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

#include <soil.h>

float mixValue = 0.0f;

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

	// 3. Output the vertex position to the fragment shader using the out keyword and set the fragment’s color equal to this vertex position(see how even the vertex position values are interpolated across the triangle)

	Shader shader("Shaders/7.8.2-Shader.vert", "Shaders/7.8.2-Shader.frag");

	GLfloat data[] = {

		// VERTEX				// COLOR			 // TEXTURE

		0.5f, 0.5f, 0.0f,		1.0f,0.0f,0.0f,		1.0f, 1.0f, // 0
		0.5f, -0.5f, 0.0f,		0.0f,1.0f,0.0f,		1.0f, 0.0f, // 1
		-0.5f, -0.5f, 0.0f,		0.0f,0.0f,1.0f,		0.0f, 0.0f, // 2
		-0.5f, 0.5f, 0.0f,		1.0f,0.0f,0.0f,		0.0f, 1.0f  // 3
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	int firstWidth, firstHeight;
	unsigned char* firstImage = SOIL_load_image("container.jpg", &firstWidth, &firstHeight, 0, SOIL_LOAD_RGB);

	GLuint firstTexture;
	glGenTextures(1, &firstTexture);
	glBindTexture(GL_TEXTURE_2D, firstTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, firstWidth, firstHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, firstImage);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(firstImage);

	int secondWidth, secondHeight;
	unsigned char* secondImage = SOIL_load_image("awesomeface.png", &secondWidth, &secondHeight, 0, SOIL_LOAD_RGB);

	GLuint secondTexture;
	glGenTextures(1, &secondTexture);
	glBindTexture(GL_TEXTURE_2D, secondTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, secondWidth, secondHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, secondImage);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(secondImage);

	// .......................................
	// 10. Creating GAME LOOP:
	while (!glfwWindowShouldClose(window))
	{
		// 10.1 Checking if any events are triggered (like kbd) and calls the corresponding functions (which we can set via callback methods).
		glfwPollEvents();

		// 10.2 Rendering command here.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // state-setting function.
		glClear(GL_COLOR_BUFFER_BIT); // state-using function (uses the current state to retrieve the clearing color from).

		// ..:: DRAWING CODE (in GAME LOOP) ::..
		shader.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, firstTexture);
		glUniform1i(glGetUniformLocation(shader.getProgramID(), "firstTexture"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, secondTexture);
		glUniform1i(glGetUniformLocation(shader.getProgramID(), "secondTexture"), 1);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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