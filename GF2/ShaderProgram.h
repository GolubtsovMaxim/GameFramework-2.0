#include <map>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
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
		COMPILED
	};

	
	bool loadShaders(const char* vertexShaderFileName, const char* fragmentShaderFileName);
	void useShaders();

	void setUniform(const GLchar* name, const glm::vec2& v);
	void setUniform(const GLchar* name, const glm::vec3& v);
	void setUniform(const GLchar* name, const glm::vec4& v);
	void setUniform(const GLchar* name, const glm::mat4& m);

	GLuint getProgram() const;

private:

	std::string fileToString(const std::string& filename);
	void checkCompileErrors(GLuint shader, ShaderType type);
	GLint getUniformLocation(const GLchar* name);

	GLuint mHandle; //actual shader on the GPU
	std::map<std::string, GLint> mUniformLocations;
};
