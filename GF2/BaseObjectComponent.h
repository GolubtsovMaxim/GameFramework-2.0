#include <iostream>
#include <map>
#include <string>
#include <vector>


#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

class BaseObjectComponent
{
public:
	BaseObjectComponent(float x, float y, float z);
	~BaseObjectComponent();
private:
	glm::vec3 mPosition;
};

