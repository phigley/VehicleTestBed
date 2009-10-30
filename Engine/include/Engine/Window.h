#ifndef WINDOW_H_
#define WINDOW_H_

#include <GL/glfw.h>
#include "Engine/Vector2.h"

namespace Engine
{
	class Window
	{
	public:

		Window(int width, int height, const char* title);
		~Window();

		void setProjectionSize(float width, float height);

		Engine::Vector2 getProjectionSize() const;

		bool isOpen() const { return glfwGetWindowParam( GLFW_OPENED ) == GL_TRUE; }
	};
}

#endif // WINDOW_H_