#include <iostream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include "GL/glew.h"	
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Application.h"

bool gWireframe = false;
const std::string texture1 = "textures/BaseTexture.jpg";
const std::string texture2 = "textures/FloorTexture.jpg";
const float MOUSE_SENSITIVITY = 0.1f;
const float MOVE_SPEED = 0.1;
FPSCamera* fpsCamera = new FPSCamera(glm::vec3(0.0f, 0.0f, 5.0f));

Application::Application()
{
}


Application::~Application()
{
}

int Application::Run()
{
	WindowHandle* pWndhdl = new WindowHandle();
	Texture* pTexture = new Texture();
	Texture* pFloorTexture = new Texture();
	ShaderProgram* pShader = new ShaderProgram();
	

	if (!initOpenGL(pWndhdl))
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		return -1;
	}

	glm::vec3 cubePos = glm::vec3(5.0f, 0.0f, -5.0f);
	glm::vec3 floorPos = glm::vec3(0.0f, -1.0f, 0.0f);
	
	
	SetupGPUBuffer(pWndhdl->getVertices());

	pShader->loadShaders("shaders/basic.vert", "shaders/basic.frag");
	pTexture->loadTexture(texture1, true);
	pFloorTexture->loadTexture(texture2, true);

	double lastTime = glfwGetTime();
	float cubeAngle = 0.0f;

	// Rendering loop
	while (!glfwWindowShouldClose(pWndhdl->gWindow))
	{
		Render(pWndhdl, lastTime, pTexture, pFloorTexture, fpsCamera, cubePos, floorPos, cubeAngle, pShader);
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();

	delete pWndhdl;
	delete pShader;
	delete pTexture;

	return 0;
}

void Application::SetGLFWwindowHint(unsigned major, unsigned minor)
{
}

bool Application::initOpenGL(WindowHandle* wndhdl)
{
	if (!glfwInit())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	

	wndhdl->gWindow = glfwCreateWindow(wndhdl->gWindowWidth, wndhdl->gWindowHeight, wndhdl->getTitle(), NULL, NULL);
	if (wndhdl->gWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(wndhdl->gWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	glfwSetKeyCallback(wndhdl->gWindow, &wndhdl->glfw_onKey);
	//glfwSetFramebufferSizeCallback(wndhdl->gWindow, glfw_onFramebufferSize);

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	glViewport(0, 0, wndhdl->gWindowWidth, wndhdl->gWindowHeight);
	glEnable(GL_DEPTH_TEST);

	return true;
}

void Application::showFPS(GLFWwindow* window, WindowHandle wndhdl)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime();

	elapsedSeconds = currentSeconds - previousSeconds;

	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		std::ostringstream outs;
		outs.precision(3);
		outs << std::fixed
			<< wndhdl.getTitle() << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		frameCount = 0;
	}

	frameCount++;
}

void Application::Render(WindowHandle* InWndhdl, double InLastTime, Texture* pInTexture, Texture* pInFloorTexture, FPSCamera* InFpsCamera, glm::vec3 InCubePos,  glm::vec3 InFloorPos,float InCubeAngle, ShaderProgram* InShaderProgram)
{
	showFPS(InWndhdl->gWindow, *InWndhdl);

	double currentTime = glfwGetTime();
	double deltaTime = currentTime - InLastTime;

	// Poll for and process events
	glfwPollEvents();

	Update(deltaTime, InWndhdl, InFpsCamera);

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pInTexture->bind(0);

	glm::mat4 model(1.0), view(1.0), projection(1.0);

	model = glm::translate(model, InCubePos);

	view = InFpsCamera->getViewMatrix();

	projection = glm::perspective(glm::radians(InFpsCamera->getFOV()), (float)InWndhdl->gWindowWidth / (float)InWndhdl->gWindowHeight, 0.1f, 100.0f);

	InShaderProgram->use();

	// Pass the matrices to the shader
	InShaderProgram->setUniform("model", model);
	InShaderProgram->setUniform("view", view);
	InShaderProgram->setUniform("projection", projection);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//////////////////////////////////////////////////////////////////////////////////

	pInFloorTexture->bind(0);
	model = glm::translate(model, InFloorPos) * glm::scale(model, glm::vec3(10.0f, 0.01f, 10.0f));
	InShaderProgram->setUniform("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	////////////////////////////////////////////////////////////
	glfwSwapBuffers(InWndhdl->gWindow);

	InLastTime = currentTime;
}

void Application::SetupGPUBuffer(std::vector<GLfloat> vertices)
{
	glGenBuffers(1, &vbo);					// Generate an empty vertex buffer on the GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);		// "bind" or set as the current buffer we are working with
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);	// copy the data from CPU to GPU

	glGenVertexArrays(1, &vao);				// Tell OpenGL to create new Vertex Array Object
	glBindVertexArray(vao);					// Make it the current one

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Application::Update(double elapsedTime, WindowHandle* InWndhdl, FPSCamera* InFpsCamera) //IMPORTANT
{
	// Camera orientation
	double mouseX, mouseY;

	// Get the current mouse cursor position delta
	glfwGetCursorPos(InWndhdl->gWindow, &mouseX, &mouseY);

	// Rotate the camera the difference in mouse distance from the center screen.  Multiply this delta by a speed scaler
	InFpsCamera->rotate((float)(InWndhdl->gWindowWidth / 2.0 - mouseX) * MOUSE_SENSITIVITY, (float)(InWndhdl->gWindowHeight / 2.0 - mouseY) * MOUSE_SENSITIVITY);

	// Clamp mouse cursor to center of screen
	glfwSetCursorPos(InWndhdl->gWindow, InWndhdl->gWindowWidth / 2.0, InWndhdl->gWindowHeight / 2.0);

	// Camera FPS movement

	// Forward/backward
	if (glfwGetKey(InWndhdl->gWindow, GLFW_KEY_W) == GLFW_PRESS)
		InFpsCamera->move(MOVE_SPEED * (float)elapsedTime * InFpsCamera->getLook());
	else if (glfwGetKey(InWndhdl->gWindow, GLFW_KEY_S) == GLFW_PRESS)
		InFpsCamera->move(MOVE_SPEED * (float)elapsedTime * - InFpsCamera->getLook());

	// Strafe left/right
	if (glfwGetKey(InWndhdl->gWindow, GLFW_KEY_A) == GLFW_PRESS)
		InFpsCamera->move(MOVE_SPEED * (float)elapsedTime * - InFpsCamera->getRight());
	else if (glfwGetKey(InWndhdl->gWindow, GLFW_KEY_D) == GLFW_PRESS)
		InFpsCamera->move(MOVE_SPEED * (float)elapsedTime * InFpsCamera->getRight());

	// Up/down
	if (glfwGetKey(InWndhdl->gWindow, GLFW_KEY_Z) == GLFW_PRESS)
		InFpsCamera->move(MOVE_SPEED * (float)elapsedTime * InFpsCamera->getUp());
	else if (glfwGetKey(InWndhdl->gWindow, GLFW_KEY_X) == GLFW_PRESS)
		InFpsCamera->move(MOVE_SPEED * (float)elapsedTime * -InFpsCamera->getUp());
}