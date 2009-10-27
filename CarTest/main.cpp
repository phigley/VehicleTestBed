
#include <GL/glfw.h>
#include <math.h>
#include <stdlib.h>
#include "Vehicle.h"
#include "Engine.h"
#include <algorithm>

namespace
{
	const double   minimumFrameTime = 1/30.0;
	const float    maximumDeltaTime = 0.1f;
}




int main( void )
{
	bool running = true;

	Engine::Window window(800,600, "Vehicle Test Bed");
	window.setProjectionSize(1000,1000);

	Engine::Timer gameTime;
	Vehicle vehicle;

	while (window.isOpen())
	{
		const float dt = std::min(float(gameTime.popFrameTime()), maximumDeltaTime);

		vehicle.Update(dt);

		Engine::FrameBlock frameBlock(minimumFrameTime - gameTime.getFrameTime());

		vehicle.Render();

		if (glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS)
		{
			// Exit program.
			return 0;
		}
	}

	return 0;
}
