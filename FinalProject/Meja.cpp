#include "Meja.h"
#include "RenderEngine.h"

Meja::Meja()
{
}

Meja::~Meja()
{
}

void Meja::Init()
{
	shader = new Shader("texturedCube.vert", "texturedCube.frag");
	shader->Init();
	// Create table diffuse texture and specular texture
	mejaDiffTex = new Texture("WhiteOak_Diffuse.png");
	mejaDiffTex->Init();
	mejaSpecTex = new Texture("WhiteOak_Specular.png");
	mejaSpecTex->Init();

	// Create instance of meja
	papan_meja = new Cube(shader, mejaDiffTex, mejaSpecTex);
	papan_meja->Init();

	kaki_meja = new Cube(shader, mejaDiffTex, mejaSpecTex);
	kaki_meja->Init();
}

void Meja::DeInit()
{
	delete papan_meja;
	delete kaki_meja;
}

void Meja::SetScalePapanMeja(float sx, float sy, float sz)
{
	papan_meja->SetScale(sx, sy, sz);
}

void Meja::SetScaleKakiMeja(float sx, float sy, float sz)
{
	kaki_meja->SetScale(sx, sy, sz);
}

void Meja::SetRotationMeja(float angle, float x, float y, float z)
{
	papan_meja->SetRotation(angle, x, y, z);
	kaki_meja->SetRotation(angle, x, y, z);
}

void Meja::SetPositionPapanMeja(float x, float y, float z)
{
	papan_meja->SetPosition(x, y, z);
}

void Meja::SetPositionKakiMeja(float x, float y, float z)
{
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			kaki_meja->SetPosition(-x, y, z);
		case 1:
			kaki_meja->SetPosition(x, y, z);
		case 2:
			kaki_meja->SetPosition(-x, y, -z);
		case 3:
			kaki_meja->SetPosition(x, y, -z);
		default:
			break;
		}
	}
}

void Meja::Draw()
{
	papan_meja->Draw();
	kaki_meja->Draw();
}



