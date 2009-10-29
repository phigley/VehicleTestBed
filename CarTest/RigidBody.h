#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "Engine/Vector2.h"

// This is actually just a rectangular rigid body.  It will
// be expanded to other shapes if needed.
class RigidBody
{
public:
	struct Constants
	{
		float	mass;
		float	inertia;

		Engine::Vector2	halfSize;

		Constants(float my_mass, const Engine::Vector2& my_halfSize);
	};

public:

	RigidBody(const Constants& constants);

	void update(float dt);

	void applyForce(const Engine::Vector2& force, const Engine::Vector2& position);

	void reset();

	float getAngle() const { return angle; }
	const Engine::Vector2& getPosition() const { return position; }

private:

	const Constants& constants;

	// Orientation and position in world-space.
	float			angle;
	Engine::Vector2 position;

	float			angularVelocity;
	Engine::Vector2	velocity;

	// Forces and torques in world-space.
	Engine::Vector2 accumulatedForces;
	float			accumulatedTorque;

};

#endif // RIGIDBODY_H_
