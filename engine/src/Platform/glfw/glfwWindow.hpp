#pragma once
#include <Core/Window.hpp>

class glfwWindow : public Window
{
private:
	static void OnError(int error_code, const char* description);
	void Init(const char* title, const glm::ivec2& size);
public:
	glfwWindow(const std::string& title, const glm::ivec2& size);
	virtual ~glfwWindow();

	virtual void SetTitle(const std::string title) override;
	virtual void SetSize(const glm::ivec2&) override;
	virtual glm::ivec2 GetSize() const override;
	
	virtual void SetVSync(bool) override;
	virtual bool IsVSync() const override { return m_data.m_IsVSync; }
	// Set the icon by loading it from the specified file path in assets/images
	virtual void SetIcon(const std::string& iconFile) override;

	virtual void SetEventCallback(const EventFnCallback<>& eventFn) override { m_data.m_Callback = eventFn; }
	// Updates events and swaps the window buffers
	virtual void OnUpdate() const override;

	virtual void* GetNativeWindow() const override { return m_data.m_Handle; }
private:
	struct WindowInfo 
	{
		EventFnCallback<> m_Callback;
		void* m_Handle = 0;
		bool m_IsVSync = false;
	} m_data;
	static int s_WindowCount;
};