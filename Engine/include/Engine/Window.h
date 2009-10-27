#ifndef WINDOW_H_
#define WINDOW_H_

#include <GL/glfw.h>

namespace Engine
{
	class Window
	{
	public:

		Window(int width, int height, const char* title);
		~Window();

		bool isOpen() const { return glfwGetWindowParam( GLFW_OPENED ) == GL_TRUE; }
	};
}

#endif // WINDOW_H_