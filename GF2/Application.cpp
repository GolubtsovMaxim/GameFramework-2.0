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
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(pWindow))
	{
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		if (!glfwInit())
		{
			return false;
		}

		pWindowHandle = new WindowHandle();
		GLFWwindow* pWindow = glfwCreateWindow(pWindowHandle->mWindowWidth, pWindowHandle->mWindowHeight, pWindowHandle->getGameWindowTitle(), nullptr, nullptr);

		pWindowHandle->getVerticesArr(); //previously

		SetGLFWwindowHint(3, 3);
		
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

void Application::Render(GLFWwindow* pInWindow)
{
	while (!glfwWindowShouldClose(pInWindow))
	{
		glfwPollEvents();

		glClearColor(0.83f, 0.18f, 0.29f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(pInWindow);
	}
}
