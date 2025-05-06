#include "Text.hpp"
Text::Text(const std::string& content, glm::vec2 position, glm::vec2 scale, glm::vec3 color, float rotation, Alignment alignment)
	: Transformable2D(position, scale, color, rotation), m_Alignment(alignment)
{
	*this = content;
}

void Text::operator=(const std::string& content)
{
	m_Content = content;
}
