#include "Application.h"

Application::Application()
{

}

Application::~Application()
{
}

void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader_norm->setMat4("projection", projection);
	shader->setMat4("projection", projection);
}

void Application::setupCamera()
{
	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	shader_norm->setMat4("view", view);
	shader->setMat4("view", view);
}

void Application::setupLighting()
{
	// set lighting attributes
	glm::vec3 lightPos = glm::vec3( 0, 1, 0);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	shader_norm->setVec3("lightPos", lightPos);
	shader_norm->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);
	shader_norm->setVec3("lightColor", lightColor);
}


void Application::Init()
{
	// Build a lighting map shader (No Texture)
	shader_norm = new Shader("cube.vert", "cube.frag");
	shader_norm->Init();
	
	// Build a lighting map shader (Using Texture)
	shader = new Shader("texturedCube.vert", "texturedCube.frag");
	shader->Init();


	// Create table diffuse texture and specular texture
	//mejaDiffTex = new Texture("WhiteOak_Diffuse.png");
	//mejaDiffTex->Init();
	//mejaSpecTex = new Texture("WhiteOak_Diffuse.png");
	//mejaSpecTex->Init();

	// Create book diffuse texture and specular texture
	bukuDiffTex = new Texture("leather.png");
	bukuDiffTex->Init();
	bukuSpecTex = new Texture("leather.png");
	bukuSpecTex->Init();

	// Create fireplace base diffuse texture and specular texture
	fireplaceDiffTex = new Texture("Red_Clay.png");
	fireplaceDiffTex->Init();
	fireplaceSpecTex = new Texture("Red_Clay.png");
	fireplaceSpecTex->Init();

	// Create ground diffuse texture and specular texture
	groundDiffTex = new Texture("rumput.png");
	groundDiffTex->Init();
	groundSpecTex = new Texture("rumput.png");
	groundSpecTex->Init();

	// Create roof diffuse texture and specular texture
	roofDiffTex = new Texture("abuabu,jpg");
	roofDiffTex->Init();
	roofSpecTex = new Texture("abuabu.jpg");
	roofSpecTex->Init();

	// Create well with water diffuse texture and specular texture
	wellDiffTex = new Texture("dindingSumur.png");
	wellDiffTex->Init();
	wellSpecTex = new Texture("dindingSumur.png");
	wellSpecTex->Init();
	waterDiffTex = new Texture("air.jpg");
	waterDiffTex->Init();
	waterSpecTex = new Texture("air.jpg");
	waterSpecTex->Init();

	// Create counter diffuse texture and specular texture
	counterDiffTex = new Texture("counter_diffuse.jpg");
	counterDiffTex->Init();
	counterSpecTex = new Texture("counter_specular.jpg");
	counterSpecTex->Init();
	knopDiffTex = new Texture("knop_diffuse.png");
	knopDiffTex->Init();
	knopSpecTex = new Texture("knop_specular.png");
	knopSpecTex->Init();

	// Create instance of Table
	papan_meja = new ColoredCube(shader_norm);
	papan_meja->Init();

	kaki_meja = new ColoredCube(shader_norm);
	kaki_meja->Init();

	// Create instance of Book
	buku = new Cube(shader, bukuDiffTex, bukuSpecTex);
	buku->Init();
	buku->SetScale(0.2f, 0.1f, 0.3f);

	// Create instance of Fireplace
	fireplaceBase = new Cube(shader, fireplaceDiffTex, fireplaceSpecTex);
	fireplaceBase->Init();

	// Create instance of Room
	room_wall = new ColoredCube(shader_norm);
	room_wall->Init();

	// Create instance of Ground
	ground = new Cube(shader, groundDiffTex, groundSpecTex);
	ground->Init();

	// Create instance of Roof
	roof = new Cube(shader, roofDiffTex, roofSpecTex);
	roof->Init();

	// Create instance of Well and Water
	well = new Cube(shader, wellDiffTex, wellSpecTex);
	well->Init();
	water = new Cube(shader, waterDiffTex, waterSpecTex);
	water->Init();

	// Create instance of Counter
	counter = new Cube(shader, counterDiffTex, counterSpecTex);
	counter->Init();
	knop = new Cube(shader, knopDiffTex, knopSpecTex);
	knop->Init();

	// Create instance of Chair
	chair = new ColoredCube(shader_norm);
	chair->Init();

	// Create instance of Hanging Shelf
	hangingShelf = new ColoredCube(shader_norm);
	hangingShelf->Init();

	// Initialize camera
	InitCamera();


}

void Application::DeInit()
{
	delete room_wall;
	delete roof;
	delete ground;
	delete papan_meja;
	delete kaki_meja;
	delete buku;
	delete well;
	delete water;
	delete counter;
	delete knop;
	delete chair;
	delete hangingShelf;
}

void Application::Update(double deltaTime)
{
	angle += (float)((deltaTime * 0) / 1000);
	room_wall->SetRotation(angle, 0, 1, 0);
	papan_meja->SetRotation(angle, 0, 1, 0);
	kaki_meja->SetRotation(angle, 0, 1, 0);
	fireplaceBase->SetRotation(angle, 0, 1, 0);
	buku->SetRotation(angle, 0, 1, 0);
	ground->SetRotation(angle, 0, 1, 0);
	roof->SetRotation(angle, 0, 1, 0);
	well->SetRotation(angle, 0, 1, 0);
	water->SetRotation(angle, 0, 1, 0);
	counter->SetRotation(angle, 0, 1, 0);
	knop->SetRotation(angle, 0, 1, 0);
	chair->SetRotation(angle, 0, 1, 0);
	hangingShelf->SetRotation(angle, 0, 1, 0);
}

void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.9f, 1.0f, 0.9f);

	// setup perspective 
	setupPerspective();
	// setup camera
	setupCamera();
	// setup lighting
	setupLighting();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	glEnable(GL_DEPTH_TEST);

	Table();
	Table2();
	Chair();
	HangingShelf();
	Fireplace();
	Roof();
	Room();
	Ground();
	Well();
	Water();
	Counter();
	Counter2();

	glDisable(GL_DEPTH_TEST);

}

void Application::Roof()
{
	const int roofHeight = 15;
	const int roofBase = 70;

	for (int i = roofHeight; i > 0; i--)
	{
		float yPos = 18 + (roofHeight - i) + 3;
		float scale = static_cast<float>(i) / roofHeight;

		roof->SetPosition(0, yPos, 0);
		roof->SetScale(roofBase * scale, 2 * scale, roofBase * scale);
		roof->Draw();
	}
}

void Application::Ground()
{
	// Ground
	ground->SetScale(130.0f, 1.3f, 170.0f); // You can adjust the ground size
	ground->SetPosition(0, -1, 0);
	ground->Draw();
}

void Application::Well()
{
	for (int i = 0; i < 4; i++)
	{
		// switch case for building the well
		switch (i)
		{
		case 0:
			//right wall
			well->SetPosition(-20.0f, 2.0f, -69.5f);
			well->SetScale(1.0f, 7.0f, 20.0f);
			well->Draw();

		case 1:
			//left wall
			well->SetPosition(-39.0f, 2.0f, -69.5f);
			well->SetScale(1.0f, 7.0f, 20.0f);
			well->Draw();

		case 2:
			//front wall
			well->SetPosition(-30.0f, 2.0f, -60.0f);
			well->SetScale(19.0f, 7.0f, 1.0f);
			well->Draw();

		case 3:
			//back wall
			well->SetPosition(-30.0f, 2.0f, -79.0f);
			well->SetScale(19.0f, 7.0f, 1.0f);
			well->Draw();
		}
	}
}

void Application::Water()
{
	water->SetPosition(-30.0f, -1.0f, -69.5f);
	water->SetScale(19.0f, 3.0f, 19.0f);
	water->Draw();
}

void Application::Room()
{
	room_wall->SetColor(125.0f, 63.0f, 0);
	
	for (int i = 0; i < 10; i++)
	{
		// switch case for building the room
		switch (i)
		{
		case 0:
			// Top wall (Roof)
			room_wall->SetScale(45.0f, 3.0f, 60.0f);
			room_wall->SetPosition(0, 18.0f, 0);
			room_wall->Draw();

		case 1:
			// Bottom wall (Floor)
			room_wall->SetScale(45.0f, 0.7f, 60.0f);
			room_wall->SetPosition(0, 0, 0);
			room_wall->Draw();

		case 2:
			// Back wall
			room_wall->SetScale(40.0f, 18.0f, 3.0f);
			room_wall->SetPosition(0, 9.0f, -30.0f);
			room_wall->Draw();

		case 3:
			// Right wall
			room_wall->SetScale(3.0f, 18.0f, 60.0f);
			room_wall->SetPosition(21.0f, 9.0f, 0);
			room_wall->Draw();

		case 4:
			// Left wall
			room_wall->SetScale(3.0f, 18.0f, 60.0f);
			room_wall->SetPosition(-21.0f, 9.0f, 0);
			room_wall->Draw();

		case 5:
			// Front left wall
			room_wall->SetScale(13.0f, 20.0f, 2.0f);
			room_wall->SetPosition(-16.0f, 9.0f, 31.0f);
			room_wall->Draw();

		case 6:
			// Front right wall
			room_wall->SetScale(13.0f, 20.0f, 2.0f);
			room_wall->SetPosition(16.0f, 9.0f, 31.0f);
			room_wall->Draw();

		case 7:
			// Front up wall
			room_wall->SetScale(45.0f, 5.0f, 2.0f);
			room_wall->SetPosition(0.0f, 17.0f, 31.0f);
			room_wall->Draw();

		case 8:
			// Sekat left wall
			room_wall->SetScale(30.0f, 20.0f, 2.0f);
			room_wall->SetPosition(-4.5f, 9.0f, 8.0f);
			room_wall->Draw();

		case 9:
			// Sekat up wall
			room_wall->SetScale(39.0f, 5.0f, 2.0f);
			room_wall->SetPosition(0.0f, 17.0f, 8.0f);
			room_wall->Draw();
		}
	}
}

void Application::HangingShelf()
{
	hangingShelf->SetColor(102.0f, 44.0f, 0.0f);
	for (int i = 0; i < 10; i++)
	{
		// switch case for building the hanging shelf
		switch (i)
		{
		case 0:
			// left wall
			hangingShelf->SetPosition(-18, 8, -10);
			hangingShelf->SetScale(3, 0.5, 12);
			hangingShelf->Draw();

		case 1:
			// left wall
			hangingShelf->SetPosition(-18, 11, -10);
			hangingShelf->SetScale(3, 0.5, 12);
			hangingShelf->Draw();

		case 2:
			// left wall
			hangingShelf->SetPosition(-18, 9, -3.75);
			hangingShelf->SetScale(3, 6, 0.5);
			hangingShelf->Draw();

		case 3:
			// left wall
			hangingShelf->SetPosition(-18, 9, -16.25);
			hangingShelf->SetScale(3, 6, 0.5);
			hangingShelf->Draw();

		case 4:
			// left wall
			hangingShelf->SetPosition(-18, 7, -10);
			hangingShelf->SetScale(0.5, 0.5, 12);
			hangingShelf->Draw();

		case 5:
			// right wall
			hangingShelf->SetPosition(18, 8, -10);
			hangingShelf->SetScale(3, 0.5, 12);
			hangingShelf->Draw();

		case 6:
			// right wall
			hangingShelf->SetPosition(18, 11, -10);
			hangingShelf->SetScale(3, 0.5, 12);
			hangingShelf->Draw();

		case 7:
			// right wall
			hangingShelf->SetPosition(18, 9, -3.75);
			hangingShelf->SetScale(3, 6, 0.5);
			hangingShelf->Draw();

		case 8:
			// right wall
			hangingShelf->SetPosition(18, 9, -16.25);
			hangingShelf->SetScale(3, 6, 0.5);
			hangingShelf->Draw();

		case 9:
			// right wall
			hangingShelf->SetPosition(18, 7, -10);
			hangingShelf->SetScale(0.5, 0.5, 12);
			hangingShelf->Draw();
		}
	}
}

void Application::Fireplace()
{	
	for (int i = 0; i < 10; i++) {
		switch (i)
		{
		case 0:
			// fireplace bottom base
			fireplaceBase->SetScale(5, 0.5f, 2);
			fireplaceBase->SetPosition(11, 0.55f, -27.45f);
			fireplaceBase->Draw();
			
		case 1:
			// fireplace left base
			fireplaceBase->SetScale(0.9f, 0.7f, 2);
			fireplaceBase->SetPosition(8.95f, 1.15f, -27.45f);
			fireplaceBase->Draw();

		case 2:
			// fireplace right base
			fireplaceBase->SetScale(0.9f, 0.7f, 2);
			fireplaceBase->SetPosition(13.05f, 1.15f, -27.45f);
			fireplaceBase->Draw();

		case 3:
			// fireplace back base
			fireplaceBase->SetScale(5, 0.7f, 0.1f);
			fireplaceBase->SetPosition(11, 1.15f, -28);
			fireplaceBase->Draw();

		case 4:
			// fireplace up base
			fireplaceBase->SetScale(5, 0.5f, 2);
			fireplaceBase->SetPosition(11, 1.75f, -27.45f);
			fireplaceBase->Draw();

		case 5:
			// fireplace up left base
			fireplaceBase->SetScale(0.85f, 1.3f, 1.5f);
			fireplaceBase->SetPosition(9.45f, 2.65f, -27.5f);
			fireplaceBase->Draw();

		case 6:
			// fireplace up right base
			fireplaceBase->SetScale(0.85f, 1.3f, 1.5f);
			fireplaceBase->SetPosition(12.55f, 2.65f, -27.5f);
			fireplaceBase->Draw();

		case 7:
			// fireplace up back base
			fireplaceBase->SetScale(3.95f, 1.3f, 0.1f);
			fireplaceBase->SetPosition(11.0f, 2.65f, -28.3f);
			fireplaceBase->Draw();

		case 8:
			// fireplace upper base
			fireplaceBase->SetScale(3.95f, 0.5f, 1.6f);
			fireplaceBase->SetPosition(11.0f, 3.55f, -27.55f);
			fireplaceBase->Draw();

		case 9:
			// fireplace hood
			fireplaceBase->SetScale(3.5f, 25.0f, 1.6f);
			fireplaceBase->SetPosition(11.0f, 16.0f, -27.55f);
			fireplaceBase->Draw();
		}
	}
	
}

void Application::Counter()
{
	for (int i = 0; i < 6; i++)
	{
		// switch case for building the counter
		switch (i)
		{
		case 0:
			counter->SetScale(2, 3.5f, 2);
			counter->SetPosition(1, 0.55f, 5.95f);
			counter->Draw();

		case 1:
			counter->SetScale(0.8f, 1.8f, 0.15f);
			counter->SetPosition(0.55f, 1.25f, 4.9f);
			counter->Draw();

		case 2:
			counter->SetScale(0.8f, 1.8f, 0.15f);
			counter->SetPosition(1.45f, 1.25f, 4.9f);
			counter->Draw();

		case 3:
			knop->SetScale(0.15f, 0.5f, 0.1f);
			knop->SetPosition(0.75f, 1.55f, 4.82f);
			knop->Draw();

		case 4:
			knop->SetScale(0.15f, 0.5f, 0.1f);
			knop->SetPosition(1.25f, 1.55f, 4.82f);
			knop->Draw();
		}
	}
}

void Application::Counter2()
{
	for (int i = 0; i < 6; i++)
	{
		// switch case for building the counter
		switch (i)
		{
		case 0:
			counter->SetScale(2, 3.5f, 2);
			counter->SetPosition(3, 0.55f, 5.95f);  // Adjusted X position
			counter->Draw();

		case 1:
			counter->SetScale(0.8f, 1.8f, 0.15f);
			counter->SetPosition(2.55f, 1.25f, 4.9f);  // Adjusted X position
			counter->Draw();

		case 2:
			counter->SetScale(0.8f, 1.8f, 0.15f);
			counter->SetPosition(3.45f, 1.25f, 4.9f);  // Adjusted X position
			counter->Draw();

		case 3:
			knop->SetScale(0.15f, 0.5f, 0.1f);
			knop->SetPosition(2.75f, 1.55f, 4.82f);  // Adjusted X position
			knop->Draw();

		case 4:
			knop->SetScale(0.15f, 0.5f, 0.1f);
			knop->SetPosition(3.25f, 1.55f, 4.82f);  // Adjusted X position
			knop->Draw();
		}
	}
}

void Application::Table()
{
	papan_meja->SetColor(102.0f, 44.0f, 0.0f);
	kaki_meja->SetColor(102.0f, 44.0f, 0.0f);
	
	papan_meja->SetScale(5, 0.5f, 15);
	papan_meja->SetPosition(10, 3, 20);
	papan_meja->Draw();

	kaki_meja->SetScale(1, 3.5f, 1);

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			kaki_meja->SetPosition(8, 1, 13);
			kaki_meja->Draw();
		case 1:
			kaki_meja->SetPosition(12, 1, 13);
			kaki_meja->Draw();
		case 2:
			kaki_meja->SetPosition(8, 1, 27);
			kaki_meja->Draw();
		case 3:
			kaki_meja->SetPosition(12, 1, 27);
			kaki_meja->Draw();
		}
	}
	
	
}

void Application::Table2()
{
	papan_meja->SetColor(102.0f, 44.0f, 0.0f);
	kaki_meja->SetColor(102.0f, 44.0f, 0.0f);

	papan_meja->SetScale(5, 0.5f, 15);
	papan_meja->SetPosition(-10, 3, 20);
	papan_meja->Draw();

	kaki_meja->SetScale(1, 3.5f, 1);

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			kaki_meja->SetPosition(-8, 1, 13);
			kaki_meja->Draw();
		case 1:
			kaki_meja->SetPosition(-12, 1, 13);
			kaki_meja->Draw();
		case 2:
			kaki_meja->SetPosition(-8, 1, 27);
			kaki_meja->Draw();
		case 3:
			kaki_meja->SetPosition(-12, 1, 27);
			kaki_meja->Draw();
		}
	}
}

void Application::Chair()
{
	chair->SetColor(102.0f, 44.0f, 0.0f);
	chair->SetScale(3, 3, 3);

	for (int i = 0; i < 4; i++)
	{
		// switch case for building the chair
		switch (i)
		{
		case 0:
			chair->SetPosition(16, 1, 23);
			chair->Draw();
			
		case 1:
			chair->SetPosition(16, 1, 17);
			chair->Draw();

		case 2:
			chair->SetPosition(-16, 1, 23);
			chair->Draw();

		case 3:
			chair->SetPosition(-16, 1, 17);
			chair->Draw();
		}
	}
}

void Application::Book()
{
	buku->SetPosition(0, 1.25f, 0);
	buku->Draw();
}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}

void Application::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 4.0f;
	posCamZ = 5.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Application::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Application::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Medieval Canteen", 
		800, 600, 
		false, 
		false);
}