#include <string>

#define GLEW_STATIC
#include "GL/glew.h"

class Texture
{
public:
	Texture();
	Texture(const Texture& txtr) {}
	virtual ~Texture();

	bool loadTexture(const std::string& fileName, bool generateMipMaps = true);
	void bind(GLuint texUnit = 0);

private:
	
	Texture& operator = (const Texture& txtr) {}

	GLuint mTexture;
};
