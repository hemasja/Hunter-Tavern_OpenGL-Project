#pragma once
#include <glad/glad.h>
#include <SOIL/SOIL.h>

class Texture
{
public:
	Texture(const char* texturePath);
	void Init();
	void Use(GLenum texture);
private:
	GLuint textureID;
	const char* texturePath;
};

