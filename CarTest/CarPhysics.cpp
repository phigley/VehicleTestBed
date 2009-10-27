#include "CarPhysics.h"
#include <math.h>
#include <algorithm>

// This car physics borrows heavily from Monstrous' car physics tutorial 
// originally at http://home.planet.nl/~monstrous .  That link is bad but this link works 
// http://regedit.gamedev.pl/Mirror/Car%20Physics%20for%20Games/Car%20Physics%20for%20Games.html .
// The downloadable code is available at mirrors, consult with the almighty Google.

//typedef struct VEC2
//{
//	double 	x,y;
//} VEC2;

//typedef struct CAR
//{
//	CarType	*cartype;			// pointer to static car data
//
//	VEC2	position_wc;		// position of car center in world coordinates
//	VEC2	velocity_wc;		// velocity vector of car in world coordinates
//
//	float	angle;				// angle of car body orientation (in radians)
//	float	angularvelocity;
//
//	float	steerangle;			// angle of steering (input)
//	float	throttle;			// amount of throttle (input)
//	float	brake;				// amount of braking (input)
//} CAR;

/* Lots of globals, so their value may be printed on screen
 * normally most of these variables should be private to the physics function.
 */
//	Vector2	velocity(Vector2::Empty);
//	Vector2	acceleration_wc(Vector2::Empty);
//	float	rot_angle;
//	float	sideslip;
//	float	slipanglefront;
//	float	slipanglerear;
//	Vector2	force(Vector2::Empty);
	int		rear_slip;
	int		front_slip;
//	Vector2	resistance(Vector2::Empty);
//	Vector2	acceleration(Vector2::Empty);
//	float	torque;
//	float	angular_acceleration;
//	float	yawspeed;
//	float	weight;
//	Vector2	ftraction(Vector2::Empty);
//	Vector2	flatf(Vector2::Empty);
//	Vector2 flatr(Vector2::Empty);


namespace
{
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

/*
 * Physics module
 */
//void init_cartypes( void )
//{
//	CarType	*cartype;
//
//	cartype = &cartypes[0];
//	cartype->b = 1.0;					// m
//	cartype->c = 1.0;					// m
//	cartype->wheelbase = cartype->b + cartype->c;
//	cartype->h = 1.0;					// m
//	cartype->mass = 1500;				// kg
//	cartype->inertia = 1500;			// kg.m
//	cartype->width = 1.5;				// m
//	cartype->length = 3.0;				// m, must be > wheelbase
//	cartype->wheellength = 0.7f;
//	cartype->wheelwidth = 0.3f;
//}

//void init_car( CAR *car, CarType *cartype )
//{
//	car->cartype = cartype;
//
//	car->position_wc.x = 0;
//	car->position_wc.y = 0;
//	car->velocity_wc.x = 0;
//	car->velocity_wc.y = 0;
//
//	car->angle = 0;
//	car->angularvelocity = 0;
//
//	car->steerangle = 0;
//	car->throttle = 0;
//	car->brake = 0;
//}

// These constants are arbitrary values, not realistic ones.

const float	DRAG		= 5.0f;		 		/* factor for air resistance (drag) 	*/
const float	RESISTANCE 	= 30.0f;			/* factor for rolling resistance */
const float	CA_R		= -5.20f;			/* cornering stiffness */
const float	CA_F		= -5.0f;			/* cornering stiffness */
const float	MAX_GRIP	= 2.0f;				/* maximum (normalized) friction force, =diameter of friction circle */
const float GRAVITY		= 9.8f;				/* gravity (m/s^2) */

//void do_physics( CAR *car, float delta_t )
//{
//	sn = sin(car->angle);
//	cs = cos(car->angle);
//
//	if( car->steerangle != 0.0f )
//	{
//		int breakme = 1;
//	}
//
//	// SAE convention: x is to the front of the car, y is to the right, z is down
//
//	//	bangz: Velocity of Car. Vlat and Vlong
//	// transform velocity in world reference frame to velocity in car reference frame
//	velocity.x =  cs * car->velocity_wc.y + sn * car->velocity_wc.x;
//	velocity.y = -sn * car->velocity_wc.y + cs * car->velocity_wc.x;
//
//// Lateral force on wheels
////
//	// Resulting velocity of the wheels as result of the yaw rate of the car body
//	// v = yawrate * r where r is distance of wheel to CG (approx. half wheel base)
//	// yawrate (ang.velocity) must be in rad/s
//	//
//	yawspeed = car->cartype->wheelbase * 0.5 * car->angularvelocity;
//
//	//bangz: velocity.x = fVLong_, velocity.y = fVLat_
//	if( velocity.x == 0 )		// TODO: fix singularity
//		rot_angle = 0;
//	else
//		rot_angle = atan2( yawspeed, velocity.x);
//
//	// Calculate the side slip angle of the car (a.k.a. beta)
//	if( velocity.x == 0 )		// TODO: fix singularity
//		sideslip = 0;
//	else
//		sideslip = atan2( velocity.y, velocity.x);
//
//	// Calculate slip angles for front and rear wheels (a.k.a. alpha)
//	slipanglefront = sideslip + rot_angle - car->steerangle;
//	slipanglerear  = sideslip - rot_angle;
//
//	// weight per axle = half car mass times 1G (=9.8m/s^2)
//	weight = car->cartype->mass * 9.8 * 0.5;
//
//	// lateral force on front wheels = (Ca * slip angle) capped to friction circle * load
//	flatf.x = 0;
//	flatf.y = CA_F * slipanglefront;
//	flatf.y = std::min(MAX_GRIP, flatf.y);
//	flatf.y = std::max(-MAX_GRIP, flatf.y);
//	flatf.y *= weight;
//	if(front_slip)
//		flatf.y *= 0.5;
//
//	// lateral force on rear wheels
//	flatr.x = 0;
//	flatr.y = CA_R * slipanglerear;
//	flatr.y = std::min(MAX_GRIP, flatr.y);
//	flatr.y = std::max(-MAX_GRIP, flatr.y);
//	flatr.y *= weight;
//	if(rear_slip)
//		flatr.y *= 0.5;
//
//	// longititudinal force on rear wheels - very simple traction model
//	ftraction.x = 100*(car->throttle - car->brake*signum(velocity.x));
//	ftraction.y = 0;
//	if(rear_slip)
//		ftraction.x *= 0.5;
//
//// Forces and torque on body
//
//	// drag and rolling resistance
//	resistance.x = -( RESISTANCE*velocity.x + DRAG*velocity.x*abs(velocity.x) );
//	resistance.y = -( RESISTANCE*velocity.y + DRAG*velocity.y*abs(velocity.y) );
//
//	// sum forces
//	force.x = ftraction.x + sin(car->steerangle) * flatf.x + flatr.x + resistance.x;
//	force.y = ftraction.y + cos(car->steerangle) * flatf.y + flatr.y + resistance.y;
//
//	// torque on body from lateral forces
//	torque = car->cartype->b * flatf.y - car->cartype->c * flatr.y;
//
//// Acceleration
//
//	// Newton F = m.a, therefore a = F/m
//	acceleration.x = force.x/car->cartype->mass;
//	acceleration.y = force.y/car->cartype->mass;
//
//	angular_acceleration = torque / car->cartype->inertia;
//
//// Velocity and position
//	
//	// transform acceleration from car reference frame to world reference frame
//	acceleration_wc.x =  cs * acceleration.y + sn * acceleration.x;
//	acceleration_wc.y = -sn * acceleration.y + cs * acceleration.x;
//
//	// velocity is integrated acceleration
//	//
//	car->velocity_wc.x += delta_t * acceleration_wc.x;
//	car->velocity_wc.y += delta_t * acceleration_wc.y;
//
//	// position is integrated velocity
//	//
//	car->position_wc.x += delta_t * car->velocity_wc.x;
//	car->position_wc.y += delta_t * car->velocity_wc.y;
//
//
//// Angular velocity and heading
//
//	// integrate angular acceleration to get angular velocity
//	//
//	car->angularvelocity += delta_t * angular_acceleration;
//
//	// integrate angular velocity to get angular orientation
//	//
//	car->angle += delta_t * car->angularvelocity ;
//
//}
	
/*
 * End of Physics module
 */

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
