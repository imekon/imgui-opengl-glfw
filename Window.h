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
	void getBufferSize();
	const GLint getBufferWidth() const { return bufferWidth; }
	const GLint getBufferHeight() const { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(window); }
	void swapBuffers() { glfwSwapBuffers(window); }

private:
	GLFWwindow *window;
	GLint width, height;
	GLint bufferWidth, bufferHeight;
};

