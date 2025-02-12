#pragma once
#include <glm/glm.hpp>
#include <vector>

class Snake 
{
private:
	void NextPosition();
public:
	struct Segment {
		glm::ivec2 Position, Direction;
	};

	Snake(const glm::ivec2& center);

	void Reset();

	void AddSegment();

	void Move(const glm::ivec2& direction);

	void SetColor(const glm::vec3 color) { m_Color = color; }
	
	const glm::vec3 GetColor() const { return m_Color; }
	const glm::ivec2 GetHeadPosition() const { return m_Head.Position; }	
	const std::vector<Segment> GetSegments() const { return m_Segments; }
	const bool IsSelfCollided() const;
private:
	glm::vec3 m_Color;
	
	std::vector<Segment> m_Segments;
	Segment m_Head;

	const glm::ivec2 m_Center;
};