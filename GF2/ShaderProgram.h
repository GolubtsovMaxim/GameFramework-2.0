#include <string>
#include <map>

#define GLEW_STATIC
#include "GL/glew.h"
#include "glm/glm.hpp"

class ShaderProgram
{
public:
	 ShaderProgram();
	~ShaderProgram();

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	bool loadShaders(const char* vsFilename, const char* fsFilename);
	void use();

	GLuint getProgram() const;

	void setUniform(const GLchar* name, const glm::vec2& v);
	void setUniform(const GLchar* name, const glm::vec3& v);
	void setUniform(const GLchar* name, const glm::vec4& v);
	void setUniform(const GLchar* name, const glm::mat4& m);

	GLint getUniformLocation(const GLchar * name);

private:

	std::string fileToString(const std::string& filename);
	void checkCompileErrors(GLuint shader, ShaderType type);

	GLuint mHandle;
	std::map<std::string, GLint> mUniformLocations;
};
