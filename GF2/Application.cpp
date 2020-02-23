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

Application::Application()
{
}


Application::~Application()
{
}

int Application::Run()
{
	WindowHandle* pWndhdl = new WindowHandle;
	Texture* pTexture = new Texture;
	ShaderProgram* pShader = new ShaderProgram;

	if (!initOpenGL(pWndhdl))
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		return -1;
	}

	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, -5.0f);
	
	SetupGPUBuffer(pWndhdl->getVertices());

	pShader->loadShaders("shaders/basic.vert", "shaders/basic.frag");
	pTexture->loadTexture(texture1, true);

	double lastTime = glfwGetTime();
	float cubeAngle = 0.0f;

	// Rendering loop
	while (!glfwWindowShouldClose(pWndhdl->gWindow))
	{
		Render(pWndhdl, lastTime, pTexture, cubePos, cubeAngle, pShader);
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

void Application::Render(WindowHandle* InWndhdl, double InLastTime, Texture* pInTexture, glm::vec3 InCubePos, float InCubeAngle, ShaderProgram* InShaderProgram)
{
	showFPS(InWndhdl->gWindow, *InWndhdl);

	double currentTime = glfwGetTime();
	double deltaTime = currentTime - InLastTime;

	// Poll for and process events
	glfwPollEvents();

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pInTexture->bind(0);

	glm::mat4 model(1.0), view(1.0), projection(1.0);

	InCubeAngle += (float)(deltaTime * 50.0f);
	if (InCubeAngle >= 360.0f) InCubeAngle = 0.0f;

	model = glm::translate(model, InCubePos) * glm::rotate(model, glm::radians(InCubeAngle), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 camPos(0.0f, 0.0f, 0.0f);
	glm::vec3 targetPos(0.0f, 0.0f, -1.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(camPos, camPos + targetPos, up);

	projection = glm::perspective(glm::radians(45.0f), (float)InWndhdl->gWindowWidth / (float)InWndhdl->gWindowHeight, 0.1f, 100.0f);

	InShaderProgram->use();

	// Pass the matrices to the shader
	InShaderProgram->setUniform("model", model);
	InShaderProgram->setUniform("view", view);
	InShaderProgram->setUniform("projection", projection);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	//////////////////////////////////////////////////////////////////////////////////

	//InShaderProgram.use();

	// Pass the matrices to the shader
	/*InShaderProgram.setUniform("model", model);
	InShaderProgram.setUniform("view", view);
	InShaderProgram.setUniform("projection", projection);*/

	glBindVertexArray(vao);
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
