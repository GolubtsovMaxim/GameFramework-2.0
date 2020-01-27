#include "Application.h"



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

	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(pWindow))
	{
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		//GLFWwindow* pWindow = glfwCreateWindow(pWindowHandle->mWindowWidth, pWindowHandle->mWindowHeight, pWindowHandle->getGameWindowTitle(), nullptr, nullptr);

		pWindowHandle->getVerticesArr(); //previously

		Render(pWindow);

		glfwTerminate();

		return 0;
	}

	return 1;
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
	GLuint vbo, vao;

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

void Application::Render(GLFWwindow* pInWindow)
{
	while (!glfwWindowShouldClose(pInWindow))
	{
		glfwPollEvents();

		glClearColor(0.43f, 0.58f, 0.79f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(pInWindow);
	}
}
