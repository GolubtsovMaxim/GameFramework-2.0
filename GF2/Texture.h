#include <iostream>
#include <string>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"


class Texture
{
public:
	Texture();
	virtual ~Texture();

	bool loadTexture(const std::string& fileName, bool generateMipMaps = true);
	void bind(GLuint texUnit = 0);

private:
	Texture(const Texture& texr) {}
	Texture& operator = (const Texture& texr) {}

	GLuint mTexture;
};
