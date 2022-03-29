/*

TASK: Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data.

II METHOD (2 different VAO and 2 different shader programs) => On the same frame buffer!

*/

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

/// <summary>
/// Reading to const char* data from file.
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
std::string readFromFile(const char* name)
{
	// 1. Declaring and initializing variables for storing data.
	std::string line, text;

	// 2. Declaring and initializing variable to read stream data from file.
	std::ifstream in(name);

	// 3. Reading.
	while (std::getline(in, line))
	{
		text += line + "\n";
	}

	// 4. Returning the result.
	return text;
}

/// <summary>
/// Compiling the shader and getting shader's id.
/// </summary>
/// <param name="nameOfFile"></param>
/// <param name="typeOfShader"></param>
/// <returns></returns>
GLuint getCompiledShader(const char* nameOfFile, GLenum typeOfShader)
{
	// 1. Getting data from file.
	std::string src = readFromFile(nameOfFile);
	const char* _src = src.c_str();

	// 2. Creating shader.
	GLuint shaderID = glCreateShader(typeOfShader);
	glShaderSource(shaderID, 1, &_src, NULL);
	glCompileShader(shaderID);

	// 3. Checking if compiled is done correctly.
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 4. Giving an id;
	return shaderID;
}

/// <summary>
/// Compile shader and print logs about that shader.
/// </summary>
/// <param name="nameOfFile"></param>
/// <param name="typeOfShader"></param>
/// <returns></returns>
GLuint getCompiledShader_WITH_LOGS(const char* nameOfFile, GLenum typeOfShader)
{
	// 1. Getting data from file.
	std::string src = readFromFile(nameOfFile);
	const char* _src = src.c_str();

	// 2. Creating shader.
	GLuint shaderID = glCreateShader(typeOfShader);
	glShaderSource(shaderID, 1, &_src, NULL);
	glCompileShader(shaderID);

	// 3. Checking if compiled is done correctly.
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// EXTRA:
	std::cout << "----------------------" << "\n";
	std::cout << "Name of file: " << nameOfFile << "\n";
	switch (typeOfShader)
	{
	case GL_VERTEX_SHADER:
		std::cout << "Type: Vertex Shader\n";
		break;
	case GL_FRAGMENT_SHADER:
		std::cout << "Type: Fragment Shader\n";
		break;
	}
	std::cout << "ID: " << shaderID << "\n";
	std::cout << "Content: \n";
	std::cout << src << "\n";
	std::cout << "----------------------" << "\n";

	// 4. Giving an id;
	return shaderID;
}

/// <summary>
/// Create program.
/// </summary>
/// <param name="idVertexShader"></param>
/// <param name="idFragmentShader"></param>
/// <returns></returns>
GLuint getLinkedProgram(GLuint idVertexShader, GLuint idFragmentShader)
{
	// 1. Getting an id of the program.
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	// 2. Attaching Vertex Shader.
	glAttachShader(shaderProgram, idVertexShader);
	
	// 3. Attaching Fragment Shader.
	glAttachShader(shaderProgram, idFragmentShader);

	// 4. Linking program.
	glLinkProgram(shaderProgram);

	// 5. Checking the status.
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}
	else
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
		std::cout << "Linked correctly!" << "\n";
		std::cout << "Vertex Shader ID: " << idVertexShader << "\n";
		std::cout << "Fragment Shader ID: " << idFragmentShader << "\n";
		std::cout << "Shader Program ID: " << shaderProgram << "\n";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	}


	glDeleteShader(idVertexShader);
	glDeleteShader(idFragmentShader);

	// 6. Returning an id.
	return shaderProgram;
}

/// <summary>
/// Create a program by using path to files.
/// </summary>
/// <param name="vertexShaderPath"></param>
/// <param name="fragmentShaderPath"></param>
/// <returns></returns>
GLuint getLinkedProgram_PATHS_TO_FILES(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	// 0. Getting shaders.
	GLuint idVertexShader = getCompiledShader(vertexShaderPath.c_str(), GL_VERTEX_SHADER);
	GLuint idFragmentShader = getCompiledShader(fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

	// 1. Getting an id of the program.
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	// 2. Attaching Vertex Shader.
	glAttachShader(shaderProgram, idVertexShader);

	// 3. Attaching Fragment Shader.
	glAttachShader(shaderProgram, idFragmentShader);

	// 4. Linking program.
	glLinkProgram(shaderProgram);

	// 5. Checking the status.
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}
	else
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
		std::cout << "Linked correctly!" << "\n";
		std::cout << "Vertex Shader ID: " << idVertexShader << "\n";
		std::cout << "Fragment Shader ID: " << idFragmentShader << "\n";
		std::cout << "Shader Program ID: " << shaderProgram << "\n";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	}

	glDeleteShader(idVertexShader);
	glDeleteShader(idFragmentShader);

	// 6. Returning an id.
	return shaderProgram;
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

	// 1. Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data.

	std::string srcVertexShader = "Shaders/secondVertexShader.vert";
	std::string srcFragmentShader = "Shaders/secondFragShader.frag";

	std::string srcOtherVertexShader = "Shaders/firstVertexShader.vert";
	std::string srcOtherFragmentShader = "Shaders/firstFragShader.frag";

	GLuint leftShader = getLinkedProgram_PATHS_TO_FILES(srcVertexShader, srcFragmentShader);
	GLuint rightShader = getLinkedProgram_PATHS_TO_FILES(srcOtherVertexShader, srcOtherFragmentShader);

	GLfloat leftVertices[] = {
	-1.0f, -0.5f, 0.0f,
	0.0f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	};

	GLfloat rightVertices[] = {
		0.0f, -0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	GLuint leftVAO;
	glGenVertexArrays(1, &leftVAO);
	glBindVertexArray(leftVAO);
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(leftVertices), leftVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GLuint rightVAO;
	glGenVertexArrays(1, &rightVAO);
	glBindVertexArray(rightVAO);
		GLuint rVBO;
		glGenBuffers(1, &rVBO);
		glBindBuffer(GL_ARRAY_BUFFER, rVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rightVertices), rightVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

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
		glUseProgram(leftShader);
		glBindVertexArray(leftVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(rightShader);
		glBindVertexArray(rightVAO);
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