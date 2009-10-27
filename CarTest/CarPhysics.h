#ifndef CARPHYSICS_H_
#define CARPHYSICS_H_

#include "Engine/Vector2.h"

struct CarType
{
	float	wheelbase;		// wheelbase in m
	float	b;				// in m, distance from CG to front axle
	float	c;				// in m, idem to rear axle
	float	h;				// in m, height of CM from ground
	float	mass;			// in kg
	float	inertia;		// in kg.m
	float	length,width;
	float	wheellength,wheelwidth;

	static const CarType  BasicCar;

	CarType(float b_, float c_, float h_,
			float mass_, float ineritia_,
			float length_, float width_,
			float wheellength_, float wheelwidth_);
};

class CarPhysics
{
public:

	// A reference to the car type is used, be sure car_type
	// does not go away before this class does!
	CarPhysics(const CarType& car_type);
	~CarPhysics();

	void Update(float deltaTime, float steerangle, float throttle, float brake);

	const Engine::Vector2& getPosition() const { return position_wc; }
	float getFacing() const { return angle; }

private:

	const CarType& carType;

	Engine::Vector2	position_wc;		// position of car center in world coordinates
	Engine::Vector2	velocity_wc;		// velocity vector of car in world coordinates

	float	angle;				// angle of car body orientation (in radians)
	float	angularvelocity;
};

#endif // CARPHYSICS_H_
