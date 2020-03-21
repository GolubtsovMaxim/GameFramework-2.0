#include <sstream>


#include "ShaderProgram.h"
#include "Texture.h"
#include "WindowHandle.h"
#include "Camera.h"

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
	void Render(WindowHandle* InWndhdl, double InLastTime, Texture* pInTexture, Texture* pInFloorTexture, FPSCamera InFpsCamera, glm::vec3 InCubePos, glm::vec3 InFloorPos, float InCubeAngle, ShaderProgram* InShaderProgram);
	void SetupGPUBuffer(std::vector<GLfloat> vertices);
	void Update(double elapsedTime, WindowHandle* InWndhdl, FPSCamera InFpsCamera);
};
