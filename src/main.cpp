
#include <GL/glfw.h>
#include <math.h>
#include <stdlib.h>
#include "CarPhysics.h"
#include "Engine.h"

namespace
{
	const double   minimumFrameTime = 1/30.0;
	const float pi = 3.1415926535897932384626433832795f;
}



class Vehicle
{
public :

	Vehicle();

	void Update(float dt);
	void Render();

private:

	CarPhysics carPhysics;
};

Vehicle::Vehicle()
	: carPhysics(CarType::BasicCar)
{

}

void Vehicle::Update(float dt)
{
	carPhysics.Update(dt, 0.1f, 1000, 0);
}

void Vehicle::Render()
{
	glPushMatrix();

	// TODO : Use a matrix so that you don't have to convert to degrees.
	glRotatef(carPhysics.getFacing() * 180.0f / pi, 0.0f, 0.0f, 1.0f);
	glTranslatef(carPhysics.getPosition().x, carPhysics.getPosition().y, 0.0f);


	const GLfloat body_width = 10;
	const GLfloat body_height = 25;


	const GLfloat tire_width = 2;
	const GLfloat tire_height = 5;

	// Body
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_QUADS);
		glVertex2f(-body_width, -body_height);
		glVertex2f( body_width, -body_height);
		glVertex2f( body_width,  body_height);
		glVertex2f(-body_width,  body_height);
	glEnd();

	const GLfloat offsetWidths[] =
	{
		body_width*0.9f - tire_width,
		body_width*0.9f - tire_width,

		-body_width*0.9f + tire_width,
		-body_width*0.9f + tire_width
	};

	const GLfloat offsetHeights[] =
	{
		body_height - tire_height,
		-body_height + tire_height,
		
		body_height - tire_height,
		-body_height + tire_height,
	};

	for( int i = 0; i < 4; ++i )
	{
		glPushMatrix();
			glTranslatef(offsetWidths[i], offsetHeights[i], 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_QUADS);
				glVertex2f(-tire_width, -tire_height);
				glVertex2f( tire_width, -tire_height);
				glVertex2f( tire_width,  tire_height);
				glVertex2f(-tire_width,  tire_height);
			glEnd();

		glPopMatrix();
	}

	glPopMatrix();
}
	

int main( void )
{
	bool running = true;

	Engine::Window window(800,600, "Vehicle Test Bed");

	Engine::Timer gameTime;
	Vehicle vehicle;

	while (window.isOpen())
	{
		const float dt = float(gameTime.popFrameTime());

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
