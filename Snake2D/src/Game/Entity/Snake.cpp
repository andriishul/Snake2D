#include <Snake.h>
#include "Constants.hpp"
void Snake::NextPosition()
{
	for (int i = m_Segments.size() - 1; i > 0; --i)
		m_Segments[i] = m_Segments[i - 1];
	if (!m_Segments.empty())
		m_Segments[0] = m_Head;

	m_Head.Position += m_Head.Direction;
}

Snake::Snake(const glm::ivec2& center) : m_Center(center)
{
	Reset();
}

void Snake::Reset()
{
	m_Segments.clear();
	m_Head.Position = m_Center;
}

void Snake::AddSegment()
{
	m_Segments.push_back(m_Segments.empty() ? m_Head : m_Segments.back());
}
void Snake::Move(const glm::ivec2& direction)
{
	if (-m_Head.Direction != direction)
		m_Head.Direction = direction;

	NextPosition();
}

const bool Snake::IsSelfCollided() const
{
	for (int i = m_Segments.size() - 1; i >= 0; i--)
		if (m_Segments[i].Position == m_Head.Position)
			return true;
	return false;
}
