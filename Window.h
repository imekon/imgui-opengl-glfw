#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint width, GLint height);
	virtual ~Window();

	void initialise();
	GLFWwindow *getWindow() { return window; }
	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(window); }
	void swapBuffers() { glfwSwapBuffers(window); }

private:
	GLFWwindow *window;
	GLint width, height;
	GLint bufferWidth, bufferHeight;
};

