#pragma once
#include "Transformable2D.hpp"
#include <string>

enum class Alignment {
	Left,
	Right,
	Center
};

class Text : public Transformable2D
{
public:
	explicit Text(const std::string& content = "", glm::vec2 position = { 0.f,0.f }, glm::vec2 scale = {1.f,1.f},
		glm::vec3 color = { 1.f,1.f,1.f }, float rotation = 0.f, Alignment alignment = Alignment::Center);
	
	void operator=(const std::string& content);
	const Alignment GetAlignment() const { return m_Alignment; }
	operator const std::string() const { return m_Content; }
private:
	std::string m_Content;
	Alignment m_Alignment;
};

 