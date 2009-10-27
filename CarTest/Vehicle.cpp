#include "Vehicle.h"

#include "Engine.h"

namespace
{
	const float pi = 3.1415926535897932384626433832795f;
}

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
	
