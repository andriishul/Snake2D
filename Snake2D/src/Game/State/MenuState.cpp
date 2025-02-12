#include <MenuState.hpp>
#include "Constants.hpp"

MenuState::MenuState(GameStateContext* context) : GameState(context),
m_Difficulty(GameDifficulty::Easy),
m_Header(Text("Choose difficulty level and press enter", { 0, 15 }, { 15, 15 })),
m_DifficultyLabels({
	{
		GameDifficulty::Easy,
		Text("* Easy", { 0, 0 } ,{ 10, 10 })
	},
	{
		GameDifficulty::Medium,
		Text("* Medium", { 0, -10 } ,{ 10, 10 })
	},
	{
		GameDifficulty::Hard,
		Text("* Hard", { 0, -20 }, { 10, 10 })}
	})
{
}
void MenuState::OnKeyPressed(const KeyPressedEvent& keyPressed)
{
	switch (keyPressed.GetKey()) {
	case KeyCode::Up: 
	{
		if (m_Difficulty != GameDifficulty::Easy)
			m_Difficulty = (GameDifficulty)(static_cast<int>(m_Difficulty) - static_cast<int>(GameDifficulty::Easy));
		break;
	}
	case KeyCode::Down:
	{
		if (m_Difficulty != GameDifficulty::Hard)
			m_Difficulty = (GameDifficulty)(static_cast<int>(m_Difficulty) + static_cast<int>(GameDifficulty::Easy));
		break;
	}
	case KeyCode::Enter:
	{
		m_Context->GetMetadata().SetValue("Difficulty", static_cast<int>(m_Difficulty));
		m_Context->ChangeState("InGame");
		break;
	}
  }
}

void MenuState::OnUpdate(float deltaTime)
{
	for (auto& difficulty : m_DifficultyLabels)
		difficulty.second.SetColor(Constants::Colors::Green);
	m_DifficultyLabels[m_Difficulty].SetColor(Constants::Colors::Red);
}

void MenuState::OnRender()
{
	Renderer2D::DrawText(m_Header);
	for (auto& difficulty : m_DifficultyLabels)
		Renderer2D::DrawText(difficulty.second);
}
