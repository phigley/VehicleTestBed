#include "CarPhysics.h"
#include <math.h>
#include <algorithm>

// This car physics borrows heavily from Monstrous' car physics tutorial 
// originally at http://home.planet.nl/~monstrous .  That link is bad but this link works 
// http://regedit.gamedev.pl/Mirror/Car%20Physics%20for%20Games/Car%20Physics%20for%20Games.html .
// The downloadable code is available at mirrors, consult with the almight Google.


typedef struct CARTYPE
{
	float	wheelbase;		// wheelbase in m
	float	b;				// in m, distance from CG to front axle
	float	c;				// in m, idem to rear axle
	float	h;				// in m, height of CM from ground
	float	mass;			// in kg
	float	inertia;		// in kg.m
	float	length,width;
	float	wheellength,wheelwidth;
} CARTYPE;

typedef struct VEC2
{
	double 	x,y;
} VEC2;

typedef struct CAR
{
	CARTYPE	*cartype;			// pointer to static car data
	
	VEC2	position_wc;		// position of car centre in world coordinates
	VEC2	velocity_wc;		// velocity vector of car in world coordinates

	float	angle;				// angle of car body orientation (in rads)
	float	angularvelocity;

	float	steerangle;			// angle of steering (input)
	float	throttle;			// amount of throttle (input)
	float	brake;				// amount of braking (input)
} CAR;

CARTYPE			cartypes[1];

/* Lots of globals, so their value may be printed on screen
 * normally most of these variables should be private to the physics function.
 */
	VEC2	velocity;
	VEC2	acceleration_wc;
	double	rot_angle;
	double	sideslip;
	double	slipanglefront;
	double	slipanglerear;
	VEC2	force;
	int		rear_slip;
	int		front_slip;
	VEC2	resistance;
	VEC2	acceleration;
	double	torque;
	double	angular_acceleration;
	double	sn, cs;
	double	yawspeed;
	double	weight;
	VEC2	ftraction;
	VEC2	flatf, flatr;


namespace
{
	template< typename T >
	T signum(T x)
	{
		return x >= 0 ? +1 : -1;
	}
}

/*
 * Physics module
 */
void init_cartypes( void )
{
	CARTYPE	*cartype;

	cartype = &cartypes[0];
	cartype->b = 1.0;					// m							
	cartype->c = 1.0;					// m
	cartype->wheelbase = cartype->b + cartype->c;
	cartype->h = 1.0;					// m
	cartype->mass = 1500;				// kg			
	cartype->inertia = 1500;			// kg.m			
	cartype->width = 1.5;				// m
	cartype->length = 3.0;				// m, must be > wheelbase
	cartype->wheellength = 0.7f;
	cartype->wheelwidth = 0.3f;
}

void init_car( CAR *car, CARTYPE *cartype )
{
	car->cartype = cartype;
	
	car->position_wc.x = 0;
	car->position_wc.y = 0;
	car->velocity_wc.x = 0;
	car->velocity_wc.y = 0;

	car->angle = 0;
	car->angularvelocity = 0;

	car->steerangle = 0;
	car->throttle = 0;
	car->brake = 0;
}

// These constants are arbitrary values, not realistic ones.

#define	DRAG		5.0		 		/* factor for air resistance (drag) 	*/
#define	RESISTANCE	30.0			/* factor for rolling resistance */
#define CA_R		-5.20			/* cornering stiffness */
#define CA_F		-5.0			/* cornering stiffness */
#define MAX_GRIP	2.0				/* maximum (normalised) friction force, =diameter of friction circle */

void do_physics( CAR *car, float delta_t )
{
	sn = sin(car->angle);
	cs = cos(car->angle);

	if( car->steerangle != 0.0f )
	{
		int breakme = 1;
	}

	// SAE convention: x is to the front of the car, y is to the right, z is down

	//	bangz: Velocity of Car. Vlat and Vlong
	// transform velocity in world reference frame to velocity in car reference frame
	velocity.x =  cs * car->velocity_wc.y + sn * car->velocity_wc.x;
	velocity.y = -sn * car->velocity_wc.y + cs * car->velocity_wc.x;

// Lateral force on wheels
//	
	// Resulting velocity of the wheels as result of the yaw rate of the car body
	// v = yawrate * r where r is distance of wheel to CG (approx. half wheel base)
	// yawrate (ang.velocity) must be in rad/s
	//
	yawspeed = car->cartype->wheelbase * 0.5 * car->angularvelocity;	

	//bangz: velocity.x = fVLong_, velocity.y = fVLat_
	if( velocity.x == 0 )		// TODO: fix singularity
		rot_angle = 0;
	else
		rot_angle = atan2( yawspeed, velocity.x);

	// Calculate the side slip angle of the car (a.k.a. beta)
	if( velocity.x == 0 )		// TODO: fix singularity
		sideslip = 0;
	else
		sideslip = atan2( velocity.y, velocity.x);		

	// Calculate slip angles for front and rear wheels (a.k.a. alpha)
	slipanglefront = sideslip + rot_angle - car->steerangle;
	slipanglerear  = sideslip - rot_angle;

	// weight per axle = half car mass times 1G (=9.8m/s^2) 
	weight = car->cartype->mass * 9.8 * 0.5;	
	
	// lateral force on front wheels = (Ca * slip angle) capped to friction circle * load
	flatf.x = 0;
	flatf.y = CA_F * slipanglefront;
	flatf.y = std::min(MAX_GRIP, flatf.y);
	flatf.y = std::max(-MAX_GRIP, flatf.y);
	flatf.y *= weight;
	if(front_slip)
		flatf.y *= 0.5;

	// lateral force on rear wheels
	flatr.x = 0;
	flatr.y = CA_R * slipanglerear;
	flatr.y = std::min(MAX_GRIP, flatr.y);
	flatr.y = std::max(-MAX_GRIP, flatr.y);
	flatr.y *= weight;
	if(rear_slip)
		flatr.y *= 0.5;

	// longtitudinal force on rear wheels - very simple traction model
	ftraction.x = 100*(car->throttle - car->brake*signum(velocity.x));	
	ftraction.y = 0;
	if(rear_slip)
		ftraction.x *= 0.5;

// Forces and torque on body
	
	// drag and rolling resistance
	resistance.x = -( RESISTANCE*velocity.x + DRAG*velocity.x*abs(velocity.x) );
	resistance.y = -( RESISTANCE*velocity.y + DRAG*velocity.y*abs(velocity.y) );

	// sum forces
	force.x = ftraction.x + sin(car->steerangle) * flatf.x + flatr.x + resistance.x;
	force.y = ftraction.y + cos(car->steerangle) * flatf.y + flatr.y + resistance.y;	

	// torque on body from lateral forces
	torque = car->cartype->b * flatf.y - car->cartype->c * flatr.y;

// Acceleration
	
	// Newton F = m.a, therefore a = F/m
	acceleration.x = force.x/car->cartype->mass;
	acceleration.y = force.y/car->cartype->mass;
	
	angular_acceleration = torque / car->cartype->inertia;

// Velocity and position
	
	// transform acceleration from car reference frame to world reference frame
	acceleration_wc.x =  cs * acceleration.y + sn * acceleration.x;
	acceleration_wc.y = -sn * acceleration.y + cs * acceleration.x;

	// velocity is integrated acceleration
	//
	car->velocity_wc.x += delta_t * acceleration_wc.x;
	car->velocity_wc.y += delta_t * acceleration_wc.y;

	// position is integrated velocity
	//
	car->position_wc.x += delta_t * car->velocity_wc.x;
	car->position_wc.y += delta_t * car->velocity_wc.y;


// Angular velocity and heading

	// integrate angular acceleration to get angular velocity
	//
	car->angularvelocity += delta_t * angular_acceleration;

	// integrate angular velocity to get angular orientation
	//
	car->angle += delta_t * car->angularvelocity ;

}
	
/*
 * End of Physics module
 */

CarPhysics::CarPhysics(void)
{
}

CarPhysics::~CarPhysics(void)
{
}
