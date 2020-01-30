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
	//bool initOpenGL(GLFWwindow* inWindow);

	WindowHandle* pWindowHandle;
	GLFWwindow* pWindow = NULL;
	Texture* pTexture;
	ShaderProgram* pShaderProgram;

	GLuint vao, vbo;

private:
	void Render(GLFWwindow* pInWindow, Texture* pInTexture, glm::vec3 InCubePos, float InCubeAngle, double InDeltaTime);
	void SetupGPUBuffer(std::vector<GLfloat> vertices);
};
