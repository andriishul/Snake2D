#pragma once
#include <Graphics/2D/Renderer2D.hpp>
#include <GameStateContext.hpp>

class GameState 
{
protected:
	GameState(GameStateContext* context) : m_Context(context) {}
public:
	GameState() = delete;
	
	virtual void OnKeyPressed(const KeyPressedEvent& keyPressed) {}

	virtual void OnUpdate(float deltaTime) {}

	virtual void OnRender() {}
protected:
	GameStateContext* m_Context;
};