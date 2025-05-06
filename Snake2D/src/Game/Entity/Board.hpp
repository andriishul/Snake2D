#pragma once
#include <Entity/Sprite.hpp>
#include <Snake.h>
#include <Food.hpp>

#include <vector>
class Board 
{
private:
	void SetDimension(int width, int height, int tileSize);
public:
	Board() = default;
	// Initializes the game board with a grid of tiles, setting their size, color, and calculating their positions.
	Board(int width, int height, int tileSize, const glm::vec3 color);

	Sprite* operator[](const glm::ivec2 vecIndex);
	bool IsOn(const glm::ivec2& snakePosition) const;
	// Returns the size of the board (width and height in terms of number of tiles)
	const glm::ivec2 GetSize() const { return m_Size; }
	const glm::vec3 GetColor() const { return m_Color; }
	const glm::ivec2 GetCenter() const { return m_Center; }

	void OnRender(const Snake&, const Food&);	
private:
	glm::ivec2 m_Size;
	glm::ivec2 m_Center;
	std::vector<Sprite> m_Tiles;
	glm::vec3 m_Color;
};