
#include <GL/glfw.h>
#include <math.h>
#include <stdlib.h>
#include "Vehicle.h"
#include "GroundPlane.h"
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

	Engine::Window window(600,600, "Vehicle Test Bed");

	const float originalProjectionWidth = 50.0f;
	const float originalProjectionHeight = 50.0f;
	float projectionWidth = originalProjectionWidth;
	float projectionHeight = originalProjectionHeight;

	window.setProjectionSize(projectionWidth, projectionHeight);

	Engine::Timer gameTime;
	
	GroundPlane groundPlane(10, Engine::Color(0.25f, 0.25f, 0.25f, 0.5f), Engine::Color(0.5f,0.5f, 0.5f, 0.5f));
	
	Vehicle vehicle;
	//vehicle.setSpeed(500);

	while (window.isOpen())
	{
		const float dt = std::min(float(gameTime.popFrameTime()), maximumDeltaTime);

		if (glfwGetKey('R'))
		{
			vehicle = Vehicle();
			projectionWidth = originalProjectionWidth;
			projectionHeight = originalProjectionHeight;
			window.setProjectionSize(projectionWidth, projectionHeight);
		}

		vehicle.update(dt);

		const float mag_x = fabs(vehicle.getPosition().x)*2;
		const float mag_y = fabs(vehicle.getPosition().y)*2;
		if ( mag_y > projectionWidth || mag_x > projectionHeight )
		{
			projectionWidth = std::max(projectionWidth, mag_y);
			projectionHeight = std::max(projectionHeight, mag_x);
			window.setProjectionSize(projectionWidth, projectionHeight);
		}

		Engine::FrameBlock frameBlock(minimumFrameTime - gameTime.getFrameTime());

		groundPlane.render(window);
		vehicle.render();

		if (glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS)
		{
			// Exit program.
			return 0;
		}
	}

	return 0;
}
