#include "Level.hpp"
#include <Core/Time.hpp>
#include <Graphics/2D/Renderer2D.hpp>
#include "Constants.hpp"

Level::Level(float speed) : m_Speed(speed), m_Board(10, 10, 15, Constants::Colors::Green), 
	m_Score(0), m_NextUpdate(0.0), m_SnakePlayer(m_Board.GetCenter()), 
	m_SnakeDirection(Constants::Directions2D::Right), m_IsGameOver(false)
{
	m_SnakePlayer.SetColor(Constants::Colors::Red);
	m_Food.SetColor(Constants::Colors::Magenta);
	m_Food.SetRandomPosition(m_Board);
}


void Level::OnKeyPressed(const KeyPressedEvent& keyPressed)
{
	switch (keyPressed.GetKey())
	{
	case KeyCode::Up:
		m_SnakeDirection = Constants::Directions2D::Up;
		break;
	case KeyCode::Down:
		m_SnakeDirection = Constants::Directions2D::Down;
		break;
	case KeyCode::Right:
		m_SnakeDirection = Constants::Directions2D::Right;
		break;
	case KeyCode::Left:
		m_SnakeDirection = Constants::Directions2D::Left;
		break;
	default:
		break;
	}
}
void Level::OnUpdate(float deltaTime) 
{
	if (Time::Get() < m_NextUpdate) return;

	m_SnakePlayer.Move(m_SnakeDirection);

	if (m_SnakePlayer.IsSelfCollided() || !m_Board.IsOn(m_SnakePlayer.GetHeadPosition()))
	{
		m_IsGameOver = true;
		return;
	}

	if (m_SnakePlayer.GetHeadPosition() == m_Food.GetPosition())
	{
		m_Food.SetRandomPosition(m_Board);
		m_SnakePlayer.AddSegment();
		m_Score++;
	}
	
	m_NextUpdate = Time::Get() + (1.f / m_Speed);
}

void Level::OnRender() 
{
	m_Board.OnRender(m_SnakePlayer, m_Food);
}

