#include "Shader.h"

/// <summary>
/// Create shader by using path to vertex shader and path to fragment shader.
/// </summary>
/// <param name="vertexSourcePath"></param>
/// <param name="fragmentSourcePath"></param>
Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath)
{
    // 1. Retrive the vertex/ fragment source code.
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;

    // 2. Ensures ifstream objects can throw exceptions.
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // 3. Openning files.
        vShaderFile.open(vertexSourcePath);
        fShaderFile.open(fragmentSourcePath);
        std::stringstream vShaderStream, fShaderStream;
    
        // 4. Read file's buffer contents into stream.
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // 5. Close file handlers.
        vShaderFile.close();
        fShaderFile.close();

        // 6. Convert stream into GLchar array.
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    // 7. Converting strings to char array.
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    // 8. Compiling shaders.
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // ..:: VERTEX SHADER ::..
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    // Printing errors if any.
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ........................

    // ..:: FRAGMENT SHADER ::...
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    // Printing errors if any.
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // .........................

    // Shader Program.
    this->programID = glCreateProgram();
    glAttachShader(this->programID, vertex);
    glAttachShader(this->programID, fragment);
    glLinkProgram(this->programID);

    // Print linking errors if any.
    glGetProgramiv(this->programID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // .........................

    std::cout << "-------VERTEX SHADER----------" << "\n";
    std::cout << "Name of file: " << vertexSourcePath << "\n";
    std::cout << "ID: " << vertex << "\n";
    std::cout << "Content: \n";
    std::cout << vertexCode << "\n";
    std::cout << "----------------------" << "\n";
    std::cout << "-------FRAGMENT SHADER---------" << "\n";
    std::cout << "Name of file: " << fragmentSourcePath << "\n";
    std::cout << "ID: " << fragment << "\n";
    std::cout << "Content: \n";
    std::cout << fragmentCode << "\n";
    std::cout << "----------------------" << "\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
    std::cout << "Linked correctly!" << "\n";
    std::cout << "Vertex Shader ID: " << vertex << "\n";
    std::cout << "Fragment Shader ID: " << fragment << "\n";
    std::cout << "Shader Program ID: " << programID << "\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n";

    // Delete the shaders as they're linked into our program now and no longer necessery.
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

/// <summary>
/// Get the ID of shader program.
/// </summary>
/// <returns></returns>
GLuint Shader::getProgramID()
{
    return this->programID;
}

/// <summary>
/// Start using the program with shaders.
/// </summary>
void Shader::Use()
{
    glUseProgram(this->programID);
}

/// <summary>
/// Get location of Matrix 4.
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
GLuint Shader::getMat4(const char* name)
{
    return glGetUniformLocation(this->programID, name);
}

/// <summary>
/// Get location of float variable.
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
GLuint Shader::getFloat(const char* name)
{
    return glGetUniformLocation(this->programID, name);
}

/// <summary>
/// Get location of integer variable.
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
GLuint Shader::getInt(const char* name)
{
    return glGetUniformLocation(this->programID, name);
}