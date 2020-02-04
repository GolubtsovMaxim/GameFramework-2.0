#include <string>

#define GLEW_STATIC
#include "GL/glew.h"

class Texture
{
public:
	Texture();
	virtual ~Texture();

	bool loadTexture(const std::string& fileName, bool generateMipMaps = true);
	void bind(GLuint texUnit = 0);

private:
	Texture(const Texture& txtr) {}
	Texture& operator = (const Texture& txtr) {}

	GLuint mTexture;
};
