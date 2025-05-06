#pragma once
#include <Event/KeyEvent.hpp>
#include "GameMetadata.hpp"

class GameState;
class GameStateContext 
{
public:
	~GameStateContext();

	template<typename TState>
	void RegisterState(const std::string& stateName) 
	{
		m_StateFactories[stateName] = [this] {return new TState(this); };
	}
	
	void ChangeState(const std::string& stateName);

	void OnKeyPressed(const KeyPressedEvent& keyPressed);
	
	void OnUpdate(float deltaTime);

	void OnRender();
	
	GameMetadata& GetMetadata() { return m_Metadata; }
private:
	bool StateExists(const std::string& stateName) const;
private:
	GameMetadata m_Metadata;
	GameState* m_CurrentState = 0;
	std::map<std::string, std::function<GameState*()>> m_StateFactories;
};