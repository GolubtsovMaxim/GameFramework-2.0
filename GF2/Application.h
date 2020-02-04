#include <sstream>

#include "WindowHandle.h"
#include "Texture.h"
#include "ShaderProgram.h"

class Application
{
public:
	Application();
	~Application();

	int Run();
	void SetGLFWwindowHint(unsigned major, unsigned minor);
	bool initOpenGL(WindowHandle* wndhdl);
	void showFPS(GLFWwindow* window, WindowHandle wndhdl);
	GLuint vbo, vao;
	//void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);

private:
	void Render(GLFWwindow* pInWindow, Texture* pInTexture, glm::vec3 InCubePos, float InCubeAngle, double InDeltaTime, ShaderProgram sp);
	void SetupGPUBuffer(std::vector<GLfloat> vertices);
};

