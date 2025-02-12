#pragma once
#include <Core/gApplication.hpp>
#include <Graphics/2D/OrthoCamera.hpp>
#include <Graphics/2D/Renderer2D.hpp>

#include <GameState.hpp>


class SnakeGame : public gApplication
{
protected:
	virtual void OnWindowResized(const WindowResizedEvent& windowResized) override;

	virtual void OnEvent(const Event& event) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
public:
	~SnakeGame();
	SnakeGame();
private:
	void CreateCamera(float width, float height);
private:
	OrthoCamera m_OrthoCamera;
	GameStateContext m_Context;
};