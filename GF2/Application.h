#include <sstream>

#include "WindowHandle.h"

class Application
{
public:
	Application();
	~Application();
	
	int Run();
	void SetGLFWwindowHint(unsigned major, unsigned minor);
	//bool initOpenGL(GLFWwindow* inWindow);

	WindowHandle* pWindowHandle;
	GLFWwindow* pWindow = NULL;
private:
	void Render(GLFWwindow* pInWindow);
	void SetupGPUBuffer(std::vector<GLfloat> vertices);
};
