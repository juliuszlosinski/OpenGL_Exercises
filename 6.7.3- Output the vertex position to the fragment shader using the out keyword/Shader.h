#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> // Include glew to get all the required OpenGL shaders.

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
};
#endif
