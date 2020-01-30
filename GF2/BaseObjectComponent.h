#include <map>
#include <vector>

#include "Texture.h"

class BaseObjectComponent
{
public:
	BaseObjectComponent(float x, float y, float z);
	~BaseObjectComponent();
private:
	glm::vec3 mPosition;
};

