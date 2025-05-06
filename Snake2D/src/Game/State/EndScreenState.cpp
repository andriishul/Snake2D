#include "EndScreenState.hpp"
#include "Constants.hpp"
void EndScreenState::OnKeyPressed(const KeyPressedEvent& keyPressed)
{
	switch (keyPressed.GetKey())
	{
	case KeyCode::Enter:
		m_Context->ChangeState("Menu");
		break;
	default:
		break;
	}
}

EndScreenState::EndScreenState(GameStateContext* context) : GameState(context),
m_GameOverMessage("Game Over! Final score: " + std::to_string(m_Context->GetMetadata().GetValue<int>("Score")), {0, 50}, {15, 15}, Constants::Colors::Red),
m_RetryPrompt("Press enter to retry", { 0, 25 }, { 15, 15 }, Constants::Colors::Yellow)
{
}

void EndScreenState::OnRender()
{
	Renderer2D::DrawText(m_GameOverMessage);
	Renderer2D::DrawText(m_RetryPrompt);
}
