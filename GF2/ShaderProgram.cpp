#include "ShaderProgram.h"


#include <fstream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"


ShaderProgram::ShaderProgram() : mHandle(0)
{
}


ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(mHandle);
}


bool ShaderProgram::loadShaders(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	const GLchar* pVerterShaderSource = fileToString(vertexShaderFileName).c_str();
	const GLchar* pFragmentShaderSource = fileToString(fragmentShaderFileName).c_str();

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


	glShaderSource(VertexShader, 1, &pVerterShaderSource, NULL);
	glShaderSource(FragmentShader, 1, &pFragmentShaderSource, NULL);

	glCompileShader(VertexShader);
	checkCompileErrors(VertexShader, VERTEX);

	glCompileShader(FragmentShader);
	checkCompileErrors(FragmentShader, FRAGMENT);


	mHandle = glCreateProgram();
	glAttachShader(mHandle, VertexShader);
	glAttachShader(mHandle, FragmentShader);


	glLinkProgram(mHandle);
	checkCompileErrors(mHandle, COMPILED);

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	return true;
}


void ShaderProgram::useShaders()
{
	glUseProgram(mHandle);
}


std::string ShaderProgram::fileToString(const std::string& filename)
{
	std::stringstream bufferString;
	std::ifstream shaderSourceFile;

	if (!shaderSourceFile)
	{
		std::cerr << "Cant read shader source file.\n";
	}

	//open shader source file
	shaderSourceFile.open(filename, std::ios::in);

	//read 
	bufferString << shaderSourceFile.rdbuf();

	return bufferString.str();
}


void ShaderProgram::checkCompileErrors(GLuint shader, ShaderType type)
{
	int status = 0;
	if (type == COMPILED)
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::cerr << "Program failed to linkage\n";
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			//std::cerr << "Shader failed to compilation\n";
		}
	}
}


GLint ShaderProgram::getUniformLocation(const GLchar* name)
{
	std::map<std::string, GLint>::iterator it = mUniformLocations.find(name);

	if (it == mUniformLocations.end())
	{
		mUniformLocations[name] = glGetUniformLocation(mHandle, name);
	}
	return mUniformLocations[name];
}


void ShaderProgram::setUniform(const GLchar* name, const glm::vec2& v)
{
	GLint location = getUniformLocation(name);
	glUniform2f(location, v.x, v.y);
}


void ShaderProgram::setUniform(const GLchar* name, const glm::vec3& v)
{
	GLint location = getUniformLocation(name);
	glUniform3f(location, v.x, v.y, v.z);
}


void ShaderProgram::setUniform(const GLchar* name, const glm::vec4& v)
{
	GLint location = getUniformLocation(name);
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::mat4& m)
{
	GLint location = getUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m));
}

GLuint ShaderProgram::getProgram() const
{
	return mHandle;
}