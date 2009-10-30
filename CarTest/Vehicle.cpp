#include "Vehicle.h"

#include "Engine.h"

Vehicle::Vehicle()
	: carPhysics(CarType::BasicCar)
	, runningTime(0.0f)
	, steeringAngle(0.0f)
{
}

void Vehicle::update(float dt)
{
	runningTime += dt;
	steeringAngle = M_PI/16.0f*sinf(runningTime*M_PI);
	carPhysics.update(dt, steeringAngle, 100, 0);
}

void Vehicle::render()
{
	Engine::Matrix2Block mainMatrix(carPhysics.getPosition(), carPhysics.getFacing());


	const float body_width = 1.0f;
	const float body_height = 0.4f;


	const float tire_width = 0.2f;
	const float tire_height = 0.1f;

	// Body
	Engine::Rectangle::Draw(body_width, body_height, Engine::Color::Red);

	// Front left tire.
	{
		const Engine::Vector2 offset(body_width*0.9f - tire_width, body_height - tire_height);
		Engine::Matrix2Block tireMatrix(offset, steeringAngle);
		Engine::Rectangle::Draw(tire_width, tire_height, Engine::Color::Green);
	}

	// Front right tire.
	{
		const Engine::Vector2 offset(body_width*0.9f - tire_width, -body_height + tire_height);
		Engine::Matrix2Block tireMatrix(offset, steeringAngle);
		Engine::Rectangle::Draw(tire_width, tire_height, Engine::Color::Green);
	}

	// Rear right tire.
	{
		const Engine::Vector2 offset(-body_width*0.9f + tire_width, body_height - tire_height);
		Engine::Matrix2Block tireMatrix(offset);
		Engine::Rectangle::Draw(tire_width, tire_height, Engine::Color::Green);
	}

	// Rear left tire.
	{
		const Engine::Vector2 offset(-body_width*0.9f + tire_width, -body_height + tire_height);
		Engine::Matrix2Block tireMatrix(offset);
		Engine::Rectangle::Draw(tire_width, tire_height, Engine::Color::Green);
	}

}
	
void Vehicle::setSpeed(float speed)
{
	Engine::Vector2 velocity(speed*cosf(carPhysics.getFacing()), speed*sinf(carPhysics.getFacing()));
	carPhysics.setVelocity(velocity);
}
