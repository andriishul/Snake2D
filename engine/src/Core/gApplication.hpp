#pragma once
#include <Core/Window.hpp>
#include <memory>


class gApplication
{
protected:
	gApplication(WindowOptions options);

	virtual void OnEvent(const Event&);

	virtual void OnWindowResized(const WindowResizedEvent& windowResized);
	virtual void OnWindowClose(const WindowCloseEvent& windowClose);
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender() = 0;
public:
	virtual ~gApplication() = default;

	void Run();

	static inline const gApplication& GetInstance() { return *s_Instance; }

	const Window& GetWindow() const { return *m_Window; }
private:
	std::unique_ptr<Window> m_Window;
	bool m_IsActive;
	float m_LastFrameTime;
	static gApplication* s_Instance;
};