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
private:
	void Render(GLFWwindow* pInWindow);
};
