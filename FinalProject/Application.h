#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "ColoredCube.h"
#include "Meja.h"
#include "Shader.h"
#include "Texture.h"

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
	void InitCamera();
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	virtual void ProcessInput(GLFWwindow* window);
private:
	Shader *shader;
	Shader* shader_norm;
	//Texture *mejaDiffTex, *mejaSpecTex;
	Texture* bukuDiffTex, * bukuSpecTex;
	Texture* fireplaceDiffTex, * fireplaceSpecTex;
	Texture* groundDiffTex, * groundSpecTex;
	Texture* roofDiffTex, * roofSpecTex;
	Texture* wellDiffTex, * wellSpecTex, * waterDiffTex, * waterSpecTex;
	Texture* counterDiffTex, * counterSpecTex, *knopDiffTex, *knopSpecTex;
	ColoredCube *papan_meja;
	ColoredCube *kaki_meja;
	ColoredCube* chair;
	ColoredCube* room_wall;
	ColoredCube* hangingShelf;
	Cube* counter, *knop;
	Cube* well, * water;
	Cube* roof;
	Cube* ground;
	Cube *buku;
	Cube* fireplaceBase;
	float angle = 0;
	glm::vec3 viewPos;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	void setupPerspective();
	void setupCamera();
	void setupLighting();
	void Well();
	void Counter();
	void Counter2();
	void Water();
	void Roof();
	void Ground();
	void Room();
	void Table();
	void Table2();
	void Chair();
	void HangingShelf();
	void Book();
	void Fireplace();
	virtual void Init();
	virtual void DeInit(); 
	virtual void Update(double deltaTime);
	virtual void Render();
};

