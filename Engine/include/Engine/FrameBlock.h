#ifndef FRAMEBLOCK_H_
#define FRAMEBLOCK_H_

#include <GL/glfw.h>

namespace Engine
{
	class FrameBlock
	{
	public :

		FrameBlock(double minimumFrameTime)
			: minimumEndTime(glfwGetTime() + minimumFrameTime)
		{
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}

		~FrameBlock()
		{
			// Swap front and back rendering buffers
			glfwSwapBuffers();

			const double sleepTime = minimumEndTime - glfwGetTime();
			if (sleepTime > 0.0)
				glfwSleep(sleepTime);
		}

	private:

		const double minimumEndTime;
	};
}

#endif // FRAMEBLOCK_H_