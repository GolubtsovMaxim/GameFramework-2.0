#include "ShaderProgram.h"

class WindowHandle
{
public:
	WindowHandle();
	~WindowHandle();

	const char* getGameWindowTitle();
	static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
	std::vector<GLfloat> getVerticesArr() { return mVertices; };
	
	const unsigned mWindowWidth = 800;
	const unsigned mWindowHeight = 600;

private:
	std::vector<GLfloat> mVertices =
	{
		// front face
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
