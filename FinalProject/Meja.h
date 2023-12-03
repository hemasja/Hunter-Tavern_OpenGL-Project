#pragma once

#include "Cube.h"
#include "Texture.h"
#include "Shader.h"

class Meja
{
public:
	Meja();
	~Meja();
	void SetScalePapanMeja(float sx, float sy, float sz);
	void SetScaleKakiMeja(float sx, float sy, float sz);
	void SetRotationMeja(float angle, float x, float y, float z);
	void SetPositionPapanMeja(float x, float y, float z);
	void SetPositionKakiMeja(float x, float y, float z);
	void Draw();
	virtual void Init();
	virtual void DeInit();
private:
	Shader* shader;
	Texture* mejaDiffTex, * mejaSpecTex;
	Cube* papan_meja;
	Cube* kaki_meja;
};

