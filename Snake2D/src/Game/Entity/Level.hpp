#pragma once
#include <Board.hpp>

#include <Event/KeyEvent.hpp>

class Level 
{
public:
	Level(float speed = 0.0f);

	int GetScore() const { return m_Score; }
	bool IsGameOver() const { return m_IsGameOver; }

	void OnKeyPressed(const KeyPressedEvent& keyPressed);
	void OnUpdate(float deltaTime);    
	void OnRender();
private:
	bool m_IsGameOver;
	int m_Score;
	float m_NextUpdate, m_Speed;
	glm::ivec2 m_SnakeDirection;
	
	Board m_Board;
	Snake m_SnakePlayer;
	Food m_Food;
};
