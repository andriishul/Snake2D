#include "gApplication.hpp"
#include <Graphics/RenderCommand.hpp>
#include <Graphics/2D/Renderer2D.hpp>
#include <core/Time.hpp>

gApplication* gApplication::s_Instance = 0;

gApplication::gApplication(WindowOptions options) :
	m_Window(std::unique_ptr<Window>(Window::Create(options))), m_IsActive(true), m_LastFrameTime(0.0)
{
	RenderCommand::Init();
    Renderer2D::Init();
	m_Window->SetEventCallback(BIND_FUNCTION(gApplication::OnEvent, this));
	s_Instance = this;
}

void gApplication::OnEvent(const Event& event)
{
	EventDispatcher dispatcher = event;
	dispatcher.Invoke<WindowCloseEvent>(BIND_FUNCTION(gApplication::OnWindowClose, this));
	dispatcher.Invoke<WindowResizedEvent>(BIND_FUNCTION(gApplication::OnWindowResized, this));
}

void gApplication::OnWindowResized(const WindowResizedEvent& windowResized)
{
	RenderCommand::SetViewport(0, 0, windowResized.GetWidth(), windowResized.GetHeight());
}

void gApplication::OnWindowClose(const WindowCloseEvent& windowClose)
{
	m_IsActive = false;
}

void gApplication::Run()
{
    while (m_IsActive)
    {
        RenderCommand::Clear();
        OnRender();
        float currentFrameTime = Time::Get();
        float deltaTime = currentFrameTime - m_LastFrameTime;
        OnUpdate(deltaTime);
        m_LastFrameTime = currentFrameTime;
        m_Window->OnUpdate();
    }
}
