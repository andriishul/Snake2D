#include "SnakeGame.hpp"

#include <State/MenuState.hpp>
#include <State/EndScreenState.hpp>
#include <State/InGameState.hpp>

constexpr int HEIGHT = 720, WIDTH = 1280;
void SnakeGame::OnWindowResized(const WindowResizedEvent& windowResized)
{
	gApplication::OnWindowResized(windowResized);
	CreateCamera(windowResized.GetWidth(), windowResized.GetHeight());
}

void SnakeGame::OnEvent(const Event& event)
{
	gApplication::OnEvent(event);
	EventDispatcher dispatcher = event;
	dispatcher.Invoke<KeyPressedEvent>(BIND_FUNCTION(GameStateContext::OnKeyPressed, &m_Context));
}
void SnakeGame::OnUpdate(float deltaTime)
{
	m_Context.OnUpdate(deltaTime);
}

void SnakeGame::OnRender()
{
	Renderer2D::Begin(m_OrthoCamera);
	m_Context.OnRender();
	Renderer2D::End();
}

SnakeGame::~SnakeGame()
{
}
SnakeGame::SnakeGame() : gApplication({ "Snake2D", { WIDTH, HEIGHT } })
{
	CreateCamera(WIDTH, HEIGHT);

	m_Context.RegisterState<MenuState>("Menu");
	m_Context.RegisterState<InGameState>("InGame");         
	m_Context.RegisterState<EndScreenState>("End");

	m_Context.ChangeState("Menu");
}

void SnakeGame::CreateCamera(float width, float height)
{
	float projectionHeight = 90;

	float projectionWidth = 160; 

	m_OrthoCamera.SetProjection(-projectionWidth, projectionWidth, -projectionHeight, projectionHeight);
}
