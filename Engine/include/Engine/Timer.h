#ifndef TIMER_H_
#define TIMER_H_

#include <GL/glfw.h>

namespace Engine
{
	class Timer
	{
	public :

		Timer()
			: lastTime(glfwGetTime())
		{
		}

		double popFrameTime()
		{ 
			const double current_time = glfwGetTime();
			const double delta = current_time - lastTime;

			lastTime = current_time;
			return delta;
		}

		double getFrameTime() const
		{
			return glfwGetTime() - lastTime;
		}

	private :

		double lastTime;
	};
}

#endif // TIMER_H_