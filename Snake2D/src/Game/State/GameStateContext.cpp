#include "GameStateContext.hpp"
#include "GameState.hpp"
#include <stdexcept>
GameStateContext::~GameStateContext()
{
	delete m_CurrentState;
}

void GameStateContext::ChangeState(const std::string& stateName)
{
	if (!StateExists(stateName))
		throw std::runtime_error(stateName + " state isnot found.");
	delete m_CurrentState;
	m_CurrentState = m_StateFactories[stateName]();
}

void GameStateContext::OnKeyPressed(const KeyPressedEvent& keyPressed)
{
	m_CurrentState->OnKeyPressed(keyPressed);
}

void GameStateContext::OnUpdate(float deltaTime)
{
	m_CurrentState->OnUpdate(deltaTime);
}

void GameStateContext::OnRender()
{
	m_CurrentState->OnRender();
}

bool GameStateContext::StateExists(const std::string& stateName) const
{
	return m_StateFactories.find(stateName) != m_StateFactories.end();
}
