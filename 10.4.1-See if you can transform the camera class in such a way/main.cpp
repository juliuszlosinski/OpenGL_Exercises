// GLEW
#define GLEW_STATIC
#include <GL/glew.h> 

// WARNING: GLEW must be included before GLFW!

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Others
#include <iostream>
#include <fstream>
#include <string>

#include "Shader.h"
#include "Camera.h"

#include <soil.h>

float mixValue = 0.0f;
const float WIDTH = 800.0f;
const float HEIGHT = 600.0f;

glm::vec3 direction = glm::vec3(0.0f, 0.0f, -3.0f);

Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_UP)
		camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (key == GLFW_KEY_DOWN)
		camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (key == GLFW_KEY_RIGHT)
		camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (key == GLFW_KEY_LEFT)
		camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
}


bool firstMouse = true;
float lastX = 0;
float lastY = 0;

/// <summary>
/// Setting the callback for mouse.
/// </summary>
/// <param name="window"></param>
/// <param name="xPos"></param>
/// <param name="yPos"></param>
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLVS", nullptr, nullptr);

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
	glViewport(0, 0, WIDTH, HEIGHT);
	// x  y  width height
// Also OpenGL by using Viewport will be maping 2D coordinates (-1, 1) to coordinates on screen (800, 600).

// * Setting the callback.
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	// ..:: SETTING UP AN OBJECT TO DRAW ::...

	// 3. Output the vertex position to the fragment shader using the out keyword and set the fragment’s color equal to this vertex position(see how even the vertex position values are interpolated across the triangle)

	Shader shader = Shader("Shaders/10.4.1-Shader.vert", "Shaders/10.4.1-Shader.frag");

	GLfloat stream[] =
	{
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,

		0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f,

		-0.5f, 0.5f, 0.0f,		1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f,

		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f,

		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,
		0.5f, 0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		0.0f, 0.0f,

		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		0.0f, 0.0f
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stream), stream, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	int width;
	int height;
	unsigned char* image_data = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	GLuint firstTexture;
	glGenTextures(1, &firstTexture);
	glBindTexture(GL_TEXTURE_2D, firstTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Other

	// Stream data.
	GLfloat planeStream[] = {
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,

		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f
	};

	// Profile VAO.
	GLuint planeVAO;
	glCreateVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);
		GLuint planeVBO;
		glGenBuffers(1, &planeVBO);
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeStream), planeStream, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// Texture.
	int planeWidth, planeHeight;
	unsigned char* planeImage = SOIL_load_image("brick.jpg", &planeWidth, &planeHeight, 0, SOIL_LOAD_RGB);
	GLuint planeTexture;
	glGenTextures(1, &planeTexture);
	glBindTexture(GL_TEXTURE_2D, planeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, planeWidth, planeHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, planeImage);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_DEPTH_TEST);
	// .......................................
	// 10. Creating GAME LOOP:
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 10.1 Checking if any events are triggered (like kbd) and calls the corresponding functions (which we can set via callback methods).
		glfwPollEvents();

		// 10.2 Rendering command here.
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // state-setting function.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // state-using function (uses the current state to retrieve the clearing color from).

		// ..:: DRAWING CODE (in GAME LOOP) ::..
		shader.Use();
		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, firstTexture);
		glUniform1i(glGetUniformLocation(shader.getProgramID(), "firstTexture"), 0);

		glm::mat4 model(1.0f);
		model = glm::rotate(model, (float)glfwGetTime()*0.5f, glm::vec3(0.0f, 1.0f, 0.0f));

		GLfloat radius = 10.0f;
		GLfloat camX = sin(glfwGetTime()) * radius;
		GLfloat camZ = cos(glfwGetTime()) * radius;

		glm::mat4 view = glm::mat4(1.0f);
		view = camera.getViewMatrix();

		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 1000.0f);

		shader.putMat4("model", model);
		shader.putMat4("view", view);
		shader.putMat4("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		
		glBindVertexArray(planeVAO);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, planeTexture);
		glUniform1i(glGetUniformLocation(shader.getProgramID(), "firstTexture"), 0);
		
		shader.putMat4("view", view);
		shader.putMat4("projection", projection);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));


		shader.putMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);

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