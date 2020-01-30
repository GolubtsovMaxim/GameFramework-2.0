#include "Application.h"

#include "glm/gtc/matrix_transform.hpp"

const std::string texture1 = "textures/wooden_crate.jpg";

Application::Application()
{
}


Application::~Application()
{
}

/////////////*****************/////////////////
int Application::Run()
{
	pWindowHandle = new WindowHandle();
	pShaderProgram = new ShaderProgram();
	pTexture = new Texture();
	
	if (!glfwInit())
	{
		return false;
	}

	SetGLFWwindowHint(3, 3);
	GLFWwindow* pWindow = glfwCreateWindow(pWindowHandle->mWindowWidth, pWindowHandle->mWindowHeight, pWindowHandle->getGameWindowTitle(), nullptr, nullptr);
	
	if (pWindow == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(pWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	glfwSetKeyCallback(pWindow, WindowHandle::glfw_onKey);
	
	SetupGPUBuffer(pWindowHandle->getVerticesArr());

	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, -5.0f);

	pShaderProgram->loadShaders("shaders/basic.vert", "shaders/basic.frag");

	pTexture->loadTexture(texture1, true);

	double lastTime = glfwGetTime();
	float cubeAngle = 0.0f();

	while (!glfwWindowShouldClose(pWindow))
	{
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		Render(pWindow, pTexture, cubePos, cubeAngle, deltaTime);
		
		lastTime = currentTime;
	}
	
	//glDeleteVertexArrays(1, &vao);
	//glDeleteBuffers(1, &vbo);

	glfwTerminate();
	delete pWindowHandle;

	return 0;
}
/////////////*****************/////////////////

void Application::SetGLFWwindowHint(unsigned major, unsigned minor)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void Application::SetupGPUBuffer(std::vector<GLfloat> vertices)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);				
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Application::Render(GLFWwindow* pInWindow, Texture* pInTexture, glm::vec3 InCubePos, float InCubeAngle, double InDeltaTime)
{
	while (!glfwWindowShouldClose(pInWindow))
	{
		glfwPollEvents();

		glClearColor(0.43f, 0.58f, 0.79f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pInTexture->bind(0);

		glm::mat4 model(1.0), view(1.0), projection(1.0);

		InCubeAngle += (float)(InDeltaTime * 50.0f);
		if (InCubeAngle >= 360.0f) InCubeAngle = 0.0f;

		model = glm::translate(model, InCubePos) * glm::rotate(model, glm::radians(InCubeAngle), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::vec3 camPos (0.0f, 0.0f, 0.0f);
		glm::vec3 targetPos(0.0f, 0.0f, -1.0f);
		glm::vec3 up(0.0f, 1.0f, 0.0f);

		view = glm::lookAt(camPos, camPos + targetPos, up);

		projection = glm::perspective(glm::radians(45.0f), (float) pWindowHandle->mWindowWidth / (float)pWindowHandle->mWindowHeight, 0.1f, 100.0f);

		pShaderProgram->useShaders();

		pShaderProgram->setUniform("model", model);
		pShaderProgram->setUniform("view", view);
		pShaderProgram->setUniform("projection", projection);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(pInWindow);
	}
}
