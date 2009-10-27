#include "Vehicle.h"

#include "Engine.h"

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
	Engine::Matrix2Block mainMatrix(carPhysics.getPosition(), carPhysics.getFacing());


	const float body_width = 10;
	const float body_height = 25;


	const float tire_width = 2;
	const float tire_height = 5;

	// Body
	Engine::Rectangle::Draw(body_width, body_height, Engine::Color::Red);

	const Engine::Vector2 offsets[] =
	{
		Engine::Vector2(body_width*0.9f - tire_width, body_height - tire_height),
		Engine::Vector2(body_width*0.9f - tire_width, -body_height + tire_height),

		Engine::Vector2(-body_width*0.9f + tire_width, body_height - tire_height),
		Engine::Vector2(-body_width*0.9f + tire_width, -body_height + tire_height)
	};

	for( int i = 0; i < 4; ++i )
	{
		Engine::Matrix2Block tireMatrix(offsets[i]);
		Engine::Rectangle::Draw(tire_width, tire_height, Engine::Color::Green);
	}
}
	
void Vehicle::setSpeed(float speed)
{
	Engine::Vector2 velocity(speed*cosf(carPhysics.getFacing()), speed*sinf(carPhysics.getFacing()));
	carPhysics.setVelocity(velocity);
}
