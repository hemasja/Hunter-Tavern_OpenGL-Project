#include "ColoredCube.h"

ColoredCube::ColoredCube(Shader* shader)
{
	this->shader = shader;
	angle = vao = vbo = ebo = 0;
}


ColoredCube::~ColoredCube()
{

}

void ColoredCube::InitData()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, normal
		// front face
		-0.5f, -0.5f, 0.5f,   0.0f,  0.0f,  1.0f, // 0
		 0.5f, -0.5f, 0.5f,   0.0f,  0.0f,  1.0f, // 1
		 0.5f,  0.5f, 0.5f,   0.0f,  0.0f,  1.0f, // 2
		-0.5f,  0.5f, 0.5f,   0.0f,  0.0f,  1.0f, // 3

		// right face
		0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // 4
		0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // 5
		0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // 6
		0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // 7

		// back face
		-0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, // 8 
		 0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, // 9
		 0.5f,  0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, // 10
		-0.5f,  0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, // 11

		// left face
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, // 12
		-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, // 13
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, // 14
		-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, // 15

		// upper face
		 0.5f, 0.5f,  0.5f,   0.0f,  1.0f,  0.0f, // 16
		-0.5f, 0.5f,  0.5f,   0.0f,  1.0f,  0.0f, // 17
		-0.5f, 0.5f, -0.5f,   0.0f,  1.0f,  0.0f, // 18
		 0.5f, 0.5f, -0.5f,   0.0f,  1.0f,  0.0f, // 19

		 // bottom face
		 -0.5f, -0.5f, -0.5f,  0.0f,  -1.0f,  0.0f, // 20
		  0.5f, -0.5f, -0.5f,  0.0f,  -1.0f,  0.0f, // 21
		  0.5f, -0.5f,  0.5f,  0.0f,  -1.0f,  0.0f, // 22
		 -0.5f, -0.5f,  0.5f,  0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		// vertex order for triangles
		0,  1,  2,   0,  2,  3,   // front face
		4,  5,  6,   4,  6,  7,   // right face
		8,  9,  10,  8,  10, 11,  // back face
		12, 14, 13,  12, 15, 14,  // left face
		16, 18, 17,  16, 19, 18,  // upper face
		20, 22, 21,  20, 23, 22   // bottom face
	};

	// Generate vao, vbo, ebo
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind the Vertex Array Object first, 
	// then bind and set vertex buffer(s), 
	// and then configure vertex attributes(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Create vertex attribute pointer in VAO
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void ColoredCube::Init()
{
	// Initialize buffers
	InitData();
}


void ColoredCube::Draw()
{
	glBindVertexArray(vao);

	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::translate(model, -position);
	model = glm::rotate(model, angle, rotationAxis);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);


	shader->setVec3("objectColor", color);
	shader->setMat4("model", model);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void ColoredCube::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void ColoredCube::SetScale(float sx, float sy, float sz)
{
	scale.x = sx;
	scale.y = sy;
	scale.z = sz;
}

void ColoredCube::SetRotation(float angle, float x, float y, float z)
{
	this->angle = angle;
	rotationAxis.x = x;
	rotationAxis.y = y;
	rotationAxis.z = z;
}

void ColoredCube::SetColor(float r, float g, float b)
{
	color.x = r / 255;
	color.y = g / 255;
	color.z = b / 255;
}