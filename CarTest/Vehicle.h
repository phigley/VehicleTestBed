#ifndef VEHICILE_H_
#define VEHICILE_H_

#include "CarPhysics.h"

class Vehicle
{
public :

	Vehicle();

	void Update(float dt);
	void Render();

	const Engine::Vector2& getPosition() const { return carPhysics.getPosition(); }

	void setSpeed(float speed);

private:

	CarPhysics carPhysics;
};

#endif // VEHICILE_H_

