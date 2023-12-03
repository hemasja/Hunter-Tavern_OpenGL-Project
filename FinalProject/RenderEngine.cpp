#include "RenderEngine.h"

RenderEngine::RenderEngine() {
}


RenderEngine::~RenderEngine() {
	glfwDestroyWindow(window);
}



void RenderEngine::Start(const char* title, unsigned int width, unsigned int height, bool vsync, bool fullscreen) {

	// set app configuration
	this->screenHeight = height;
	this->screenWidth = width;

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	window = glfwCreateWindow(this->screenWidth, this->screenHeight, title, fullscreen ? monitor : NULL, NULL);
	if (window == NULL)
	{
		Err("Failed to create GLFW window");
	}

	// set window position on center of screen
	// ---------------------------------------
	if (!fullscreen) {
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowPos(window, mode->width / 4, mode->height / 4);
	}

	// set opengl context
	// ------------------
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Err("Failed to initialize GLAD");
	}

	// set vsync
	// ---------
	glfwSwapInterval(vsync ? 1 : 0);

	// user defined function
	// ---------------------
	Init();

	lastFrame = glfwGetTime() * 1000;

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// Calculate framerate and frametime
		double deltaTime = GetDeltaTime();
		GetFPS();

		// user defined function
		// ---------------------
		ProcessInput(window);
		Update(deltaTime);
		Render();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		//Debug print framerate
		PrintFrameRate();
	}

	// user defined function
	// ---------------------
	DeInit();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

double RenderEngine::GetDeltaTime()
{

	double time = glfwGetTime() * 1000;
	double delta = time - lastFrame;
	lastFrame = time;

	return delta;
}

void RenderEngine::GetFPS()
{
	if (glfwGetTime() * 1000 - last > 1000) {
		fps = _fps;
		_fps = 0;
		last += 1000;
	}
	_fps++;
}


//Prints out an error message and exits the game
void RenderEngine::Err(std::string errorString)
{
	std::cout << errorString << std::endl;
	glfwTerminate();
	exit(1);
}

static int frameCounter = 0;
void RenderEngine::PrintFrameRate() {
	//print only once every 60 frames
	frameCounter++;
	if (frameCounter == 60) {
		std::cout << "FPS: " << fps << std::endl;
		frameCounter = 0;
	}
}




