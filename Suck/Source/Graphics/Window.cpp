#include "Graphics/Window.h"

// callback functions
void window_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(const char* title, int width, int height, bool maximized)
{
	m_Title = title;
	m_Width = width;
	m_Height = height;
	m_Maximized = maximized;

	if (!init())
		glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
	{
		glfwTerminate();
		std::cout << "Failed To Initialize GLFW!" << std::endl;
		return false;
	}

	// setting window hints
	glfwWindowHint(GLFW_MAXIMIZED, m_Maximized);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	glfwMakeContextCurrent(m_Window);

	// setting Callbacks
	glfwSetFramebufferSizeCallback(m_Window, window_resize_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		std::cout << "Failed To Initialize GLAD!" << std::endl;
		return false;
	}

	return true;
}

void Window::update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::destroy()
{
	glfwDestroyWindow(m_Window);
}

bool Window::isWindowClosed()
{
	return glfwWindowShouldClose(m_Window) == 1;
}