#pragma once
#include <GameState.hpp>

#include <Enum/GameDifficulty.hpp>
class MenuState : public GameState
{
public:
	MenuState(GameStateContext* context);

	void OnKeyPressed(const KeyPressedEvent& keyPressed) override;

	void OnUpdate(float deltaTime) override;

	void OnRender() override;
private:
	const Text m_Header;
	GameDifficulty m_Difficulty; // Current difficulty level
	std::unordered_map<GameDifficulty, Text> m_DifficultyLabels; // Mapping of difficulty levels to labels

};