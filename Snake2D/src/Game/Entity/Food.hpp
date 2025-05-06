#pragma once
#include <glm/glm.hpp>

class Board;
class Food
{
public:
	void SetColor(const glm::vec3 color) { m_Color = color; }
	void SetRandomPosition(Board& board);

	glm::vec3 GetColor() const { return m_Color; }
	glm::ivec2 GetPosition() const { return m_Position; }
private:
	glm::vec3 m_Color;
	glm::ivec2 m_Position;
};