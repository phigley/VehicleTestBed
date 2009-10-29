#ifndef VEHICILE_H_
#define VEHICILE_H_

#include "CarPhysics.h"

class Vehicle
{
public :

	Vehicle();

	void update(float dt);
	void render();

	const Engine::Vector2& getPosition() const { return carPhysics.getPosition(); }

	void setSpeed(float speed);

private:

	CarPhysics	carPhysics;

	float		runningTime;
};

#endif // VEHICILE_H_

