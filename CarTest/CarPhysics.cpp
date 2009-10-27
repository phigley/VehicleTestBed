#include "CarPhysics.h"
#include <math.h>
#include <algorithm>

// This car physics borrows heavily from Monstrous' car physics tutorial 
// originally at http://home.planet.nl/~monstrous .  That link is bad but this link works 
// http://regedit.gamedev.pl/Mirror/Car%20Physics%20for%20Games/Car%20Physics%20for%20Games.html .
// The downloadable code is available at mirrors, consult with the almighty Google.


namespace
{
	// These constants are arbitrary values, not realistic ones.

	const float	DRAG		= 5.0f;		 		/* factor for air resistance (drag) 	*/
	const float	RESISTANCE 	= 30.0f;			/* factor for rolling resistance */
	const float	CA_R		= -5.20f;			/* cornering stiffness */
	const float	CA_F		= -5.0f;			/* cornering stiffness */
	const float	MAX_GRIP	= 2.0f;				/* maximum (normalized) friction force, =diameter of friction circle */
	const float GRAVITY		= 9.8f;				/* gravity (m/s^2) */

	template< typename T >
	T signum(T x)
	{
		return T(int(x > 0) - int(x < 0));
	}

	template< typename T >
	T cap(T minimum, T maximum, T value)
	{
		if (value > minimum)
		{
			if (value < maximum)
				return value;

			return maximum;
		}

		return minimum;
	}
}

const CarType CarType::BasicCar(1.0f, 1.0f, 1.0f,
	1500, 1500,
	3.0f, 1.5f,
	0.7f, 0.3f);

CarType::CarType(float b_, float c_, float h_, float mass_,
		float inertia_, float length_, float width_,
		float wheellength_, float wheelwidth_)
	: wheelbase(b_ + c_)
	, b(b_)
	, c(c_)
	, h(h_)
	, mass(mass_)
	, inertia(inertia_)
	, length(length_)
	, width(width_)
	, wheellength(wheellength_)
	, wheelwidth(wheelwidth_)
{

}

CarPhysics::CarPhysics(const CarType& car_type)
	: carType(car_type)

	, front_slip(false)
	, rear_slip(false)

	, angle(0.0f)
	, angularvelocity(0.0f)
{
}

CarPhysics::~CarPhysics()
{
}

void CarPhysics::Update(float delta_t, float steerangle, float throttle, float brake)
{
	const float sn = sin(angle);
	const float cs = cos(angle);

	// SAE convention: x is to the front of the car, y is to the right, z is down

	//	bangz: Velocity of Car. Vlat and Vlong
	// transform velocity in world reference frame to velocity in car reference frame
	const Engine::Vector2 velocity(
		 cs * velocity_wc.y + sn * velocity_wc.x,
		-sn * velocity_wc.y + cs * velocity_wc.x );

// Lateral force on wheels
//
	// Resulting velocity of the wheels as result of the yaw rate of the car body
	// v = yawrate * r where r is distance of wheel to CG (approx. half wheel base)
	// yawrate (ang.velocity) must be in rad/s
	//
	const float yawspeed = carType.wheelbase * 0.5f * angularvelocity;

	//bangz: velocity.x = fVLong_, velocity.y = fVLat_
	float rot_angle;
	if( velocity.x == 0 )		// TODO: fix singularity
		rot_angle = 0;
	else
		rot_angle = atan2( yawspeed, velocity.x);

	// Calculate the side slip angle of the car (a.k.a. beta)
	float sideslip;
	if( velocity.x == 0 )		// TODO: fix singularity
		sideslip = 0;
	else
		sideslip = atan2( velocity.y, velocity.x);

	// Calculate slip angles for front and rear wheels (a.k.a. alpha)
	const float slipanglefront = sideslip + rot_angle - steerangle;
	const float slipanglerear  = sideslip - rot_angle;

	// weight per axle = half car mass times 1G (=9.8m/s^2)
	const float weight = carType.mass * GRAVITY * 0.5f;

	// lateral force on front wheels = (Ca * slip angle) capped to friction circle * load
	float front_lateral_force = cap(-MAX_GRIP, MAX_GRIP, CA_F * slipanglefront) * weight;
	if(front_slip)
		front_lateral_force *= 0.5f;

	const Engine::Vector2 flatf(0, front_lateral_force);

	// lateral force on rear wheels
	float rear_lateral_force = cap(-MAX_GRIP, MAX_GRIP, CA_R * slipanglerear) * weight;
	if(rear_slip)
		rear_lateral_force *= 0.5f;

	const Engine::Vector2 flatr(0, rear_lateral_force);

	// longititudinal force on rear wheels - very simple traction model
	float rear_long_force = 100*(throttle - brake*signum(velocity.x));
	if(rear_slip)
		rear_long_force *= 0.5f;

	const Engine::Vector2 ftraction(rear_long_force, 0.0f);

// Forces and torque on body

	// drag and rolling resistance
	const Engine::Vector2 resistance(
		-( RESISTANCE*velocity.x + DRAG*velocity.x*abs(velocity.x) ),
		-( RESISTANCE*velocity.y + DRAG*velocity.y*abs(velocity.y) ) );

	// sum forces
	const Engine::Vector2 force(
		ftraction.x + sin(steerangle) * flatf.x + flatr.x + resistance.x,
		ftraction.y + cos(steerangle) * flatf.y + flatr.y + resistance.y );

	// torque on body from lateral forces
	const float torque = carType.b * flatf.y - carType.c * flatr.y;

// Acceleration

	// Newton F = m.a, therefore a = F/m
	const Engine::Vector2 acceleration = force / carType.mass;

	const float angular_acceleration = torque / carType.inertia;

// Velocity and position

	// transform acceleration from car reference frame to world reference frame
	const Engine::Vector2 acceleration_wc(
		 cs * acceleration.y + sn * acceleration.x,
		-sn * acceleration.y + cs * acceleration.x );

	// velocity is integrated acceleration
	//
	velocity_wc.x += delta_t * acceleration_wc.x;
	velocity_wc.y += delta_t * acceleration_wc.y;

	// position is integrated velocity
	//
	position_wc.x += delta_t * velocity_wc.x;
	position_wc.y += delta_t * velocity_wc.y;


// Angular velocity and heading

	// integrate angular acceleration to get angular velocity
	//
	angularvelocity += delta_t * angular_acceleration;

	// integrate angular velocity to get angular orientation
	//
	angle += delta_t * angularvelocity ;
}
