#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	this->vertexPath = vertexPath;
	this->fragmentPath = fragmentPath;
}

void Shader::Init()
{
	shaderID = BuildShader();
}

void Shader::Use()
{
	glUseProgram(shaderID);
}

void Shader::setInt(const GLchar *uniformName, GLint value)
{
	Use();
	glUniform1i(glGetUniformLocation(shaderID, uniformName), value);
}

void Shader::setFloat(const GLchar* uniformName, GLfloat value)
{
	Use();
	glUniform1f(glGetUniformLocation(shaderID, uniformName), value);
}

void Shader::setVec3(const GLchar* uniformName, glm::vec3 value)
{
	Use();
	glUniform3f(glGetUniformLocation(shaderID, uniformName), value.x, value.y, value.z);
}

void Shader::setMat4(const GLchar* uniformName, glm::mat4 value)
{
	Use();
	glUniformMatrix4fv(glGetUniformLocation(shaderID, uniformName), 
		1, GL_FALSE, glm::value_ptr(value));
}

void Shader::CheckShaderErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			exit(1);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			exit(1);
		}
	}
}

GLuint Shader::BuildShader()
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		exit(1);
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders
	GLuint vertex, fragment;
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	CheckShaderErrors(vertex, "VERTEX");
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	CheckShaderErrors(fragment, "FRAGMENT");
	// Shader Program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	CheckShaderErrors(program, "PROGRAM");
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return program;

}
