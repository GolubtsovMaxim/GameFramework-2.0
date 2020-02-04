#include <vector>

#define GLEW_STATIC
#include "GL/glew.h"	
#include "GLFW/glfw3.h"

class WindowHandle
{
public:
	WindowHandle();
	~WindowHandle();
	const char* getTitle() { return mAPP_TITLE; };
	std::vector<GLfloat>& getVertices() { return mVertices; };

	const unsigned gWindowWidth = 1024;
	const unsigned gWindowHeight = 768;
	GLFWwindow* gWindow = NULL;
	static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);

private:
	const char* mAPP_TITLE = "The Application";
	std::vector<GLfloat> mVertices =
	{
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		 // back face
		 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		  1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		  1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		 -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		  1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		  // left face
		  -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		  -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		  -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		  -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		  -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		  -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		  // right face
		   1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		   1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		   1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		   1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		   1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		   1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		   // top face
		  -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		   1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
		   1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		  -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		  -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
		   1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

		   // bottom face
		  -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
		   1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		   1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
		  -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
		  -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		   1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	};
};

