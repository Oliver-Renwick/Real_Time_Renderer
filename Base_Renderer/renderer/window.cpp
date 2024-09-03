#include "window.h"

namespace RE
{
	Window::Window(int width, int height, const char* title)
		:m_width{width},m_height{height},m_title{title}
	{
		Init_window();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_win);
		glfwTerminate();
	}

	void Window::Init_window()
	{
		glfwInit();
		m_win = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);


	}
}