#include "RigidBody.h"

RigidBody::Constants::Constants(float my_mass, const Engine::Vector2& my_halfSize)
	: mass(my_mass)
	// inertia
	, halfSize(my_halfSize)
{
	// Inertia for a rectangle.
	inertia = mass*halfSize.magSqr()/12.0f;
}

RigidBody::RigidBody(const RigidBody::Constants& my_constants)
	: constants(my_constants)
	, angle(0.0f)
	, position()
	, angularVelocity(0.0f)
	, velocity()
	, accumulatedForces()
	, accumulatedTorque(0.0f)
{
}

void RigidBody::update(float dt)
{
	// Linear force.
	const Engine::Vector2 acceleration = accumulatedForces / constants.mass;
	velocity += acceleration*dt;
	position += velocity*dt;


	const float angularAcceleration = accumulatedTorque / constants.inertia;
	angularVelocity += angularAcceleration*dt;
	angle += angularVelocity*dt;

	accumulatedForces = Engine::Vector2::Empty;
	accumulatedTorque = 0.0f;
}

void RigidBody::applyForce(const Engine::Vector2 &force, const Engine::Vector2& offset)
{
	accumulatedForces += force;
	accumulatedTorque += force.cross(offset - position);
}

void RigidBody::reset()
{
	angle = 0.0f;
	position = Engine::Vector2::Empty;
	angularVelocity = 0.0f;
	velocity  = Engine::Vector2::Empty;
	accumulatedForces = Engine::Vector2::Empty;
	accumulatedTorque = 0.0f;
}