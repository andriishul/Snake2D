#pragma once
#include <glm/glm.hpp>
#include <string>


class Shader 
{
public:
	virtual ~Shader() = default;

	virtual void Use() const = 0;

	virtual void SetInt(const char* name, int val) const = 0;
	virtual void SetFloat(const char* name, float val) const = 0;
	
	virtual void SetMat3(const char* name, glm::mat3 const&) const = 0;
	virtual void SetMat4(const char* name, glm::mat4 const&) const = 0;
	
	virtual void SetVec2(const char* name, glm::vec2 const&) const = 0;
	virtual void SetVec3(const char* name, glm::vec3 const&) const = 0;
	virtual void SetVec4(const char* name, glm::vec4 const&) const = 0;
}; 