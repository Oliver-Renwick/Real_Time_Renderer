#pragma once
#include <GLFW/glfw3.h>

namespace RE
{
	class Window
	{
	public:
		Window(int width, int height, const char* title);
		~Window();

		GLFWwindow* getWindow() { return m_win; }

	private:
		void Init_window();
		int m_width = 0;
		int m_height = 0;
		const char* m_title = nullptr;
		GLFWwindow* m_win;
	};

}