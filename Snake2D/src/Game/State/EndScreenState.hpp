#pragma once
#include <GameState.hpp>

class EndScreenState : public GameState
{
public:
	EndScreenState(GameStateContext* context);

	void OnKeyPressed(const KeyPressedEvent& keyPressed) override;

	void OnRender() override;
private:
	const Text m_GameOverMessage, m_RetryPrompt;
};