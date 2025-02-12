#pragma once
#include <glm/glm.hpp>

class Camera 
{
public:
	virtual const glm::mat4 GetViewProjectionMatrix() const = 0;
};