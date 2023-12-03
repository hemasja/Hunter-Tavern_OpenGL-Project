#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void Init();
	void Use();
	void setInt(const GLchar* uniformName, GLint value);
	void setFloat(const GLchar* uniformName, GLfloat value);
	void setVec3(const GLchar* uniformName, glm::vec3 value);
	void setMat4(const GLchar* uniformName, glm::mat4 value);
private:
	GLuint shaderID;
	const char *vertexPath, *fragmentPath;
	void CheckShaderErrors(GLuint shader, std::string type);
	GLuint BuildShader();
};

