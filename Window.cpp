#include "Window.h"

Window::Window() : width(width), height(height), bufferWidth(0), bufferHeight(0)
{
}


Window::Window(GLint width, GLint height) : width(width), height(height), bufferWidth(0), bufferHeight(0)
{
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

void Window::initialise()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(width, height, "ImGui OpenGL3 example", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	getBufferSize();
}

void Window::getBufferSize()
{
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
}
