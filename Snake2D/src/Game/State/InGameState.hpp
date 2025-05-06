#pragma once
#include <GameState.hpp>
#include <Entity/Level.hpp>

class InGameState : public GameState
{
public:
	InGameState(GameStateContext* context);

	void OnKeyPressed(const KeyPressedEvent& keyPressed) override;

	void OnUpdate(float deltaTime) override;

	void OnRender() override;
private:
	Text m_ScoreLabel;
	Level m_Level;
};