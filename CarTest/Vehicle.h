#ifndef VEHICILE_H_
#define VEHICILE_H_

#include "CarPhysics.h"

class Vehicle
{
public :

	Vehicle();

	void Update(float dt);
	void Render();

private:

	CarPhysics carPhysics;
};

#endif // VEHICILE_H_

