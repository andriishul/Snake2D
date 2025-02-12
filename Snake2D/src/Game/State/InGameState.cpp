#include "InGameState.hpp"
#include "Constants.hpp"

InGameState::InGameState(GameStateContext* context) :
	GameState(context), m_Level(m_Context->GetMetadata().GetValue<int>("Difficulty"))
{
	m_ScoreLabel.SetScale({ 10, 10 });
	m_ScoreLabel.SetPosition({ 0, 80 });
	m_ScoreLabel.SetColor(Constants::Colors::Green);
}

void InGameState::OnKeyPressed(const KeyPressedEvent& keyPressed)
{
	m_Level.OnKeyPressed(keyPressed);
}

void InGameState::OnUpdate(float deltaTime)
{
	if (m_Level.IsGameOver()) 
	{
		m_Context->GetMetadata().SetValue("Score", m_Level.GetScore());
		m_Context->ChangeState("End");
		return;
	}
	m_Level.OnUpdate(deltaTime);
	m_ScoreLabel = "Score: " + std::to_string(m_Level.GetScore());
}

void InGameState::OnRender()
{
	m_Level.OnRender();
	Renderer2D::DrawText(m_ScoreLabel);
}
