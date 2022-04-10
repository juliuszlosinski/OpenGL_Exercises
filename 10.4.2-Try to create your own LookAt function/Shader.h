#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> // Include glew to get all the required OpenGL shaders.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	GLuint programID; // Id of shader program.

public:
	/// <summary>
	/// Create shader by using path to vertex shader and path to fragment shader.
	/// </summary>
	/// <param name="vertexSourcePath"></param>
	/// <param name="fragmentSourcePath"></param>
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

	/// <summary>
	/// Get the ID of shader program.
	/// </summary>
	/// <returns></returns>
	GLuint getProgramID();

	/// <summary>
	/// Start using the program with shaders.
	/// </summary>
	void Use();

	/// <summary>
	/// Get location of specified matrix 4.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	GLuint getMat4(const char* name);

	/// <summary>
	/// Get location of variable type of integer.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	GLuint getInt(const char* name);

	/// <summary>
	/// Get locoation of variable type of float.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	GLuint getFloat(const char* name);

	/// <summary>
	/// Put matrix 4 to inform.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="data"></param>
	void putMat4(const char* name, const glm::mat4& data)
	{
		glUniformMatrix4fv(getMat4(name), 1, GL_FALSE, glm::value_ptr(data));
	}
};
#endif
