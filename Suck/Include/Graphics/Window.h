#pragma once

#include <ThirdParty/GLAD/glad.h>
#include <ThirdParty/GLFW/glfw3.h>
#include <iostream>


class Window
{
private:
	GLFWwindow* m_Window;
	const char* m_Title;
	int m_Width, m_Height;
	bool m_Maximized;
public:
	Window(const char* title, int width, int height, bool maximized);

	void update();
	void clear();
	void destroy();
	bool isWindowClosed();

	inline int getWidth() { return m_Width; }
	inline int getHeight() { return m_Height; }
private:
	bool init();
};