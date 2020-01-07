#include "WindowHandle.h"

static const char* mGAME_WINDOW_TITLE = "GF2";

WindowHandle::WindowHandle()
{
}

WindowHandle::~WindowHandle()
{
}

const char * WindowHandle::getGameWindowTitle()
{
	return mGAME_WINDOW_TITLE;
}

void WindowHandle::glfw_onKey(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

