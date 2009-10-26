
#include <GL/glfw.h>
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
 #define M_PI 3.1415926535897932384626433832795
#endif

namespace
{
	const GLdouble farZ = 100;

	/*****************************************************************************
	 * Calculate the angle to be passed to gluPerspective() so that a scene
	 * is visible.  This function originates from the OpenGL Red Book.
	 *
	 * Parms   : size
	 *           The size of the segment when the angle is intersected at "dist"
	 *           (ie at the outermost edge of the angle of vision).
	 *
	 *           dist
	 *           Distance from viewpoint to scene.
	 *****************************************************************************/
	GLfloat PerspectiveAngle( GLfloat size,
							  GLfloat dist )
	{
	   GLfloat radTheta, degTheta;

	   radTheta = 2.f * (GLfloat) atan2( size / 2.f, dist );
	   degTheta = (180.f * radTheta) / (GLfloat) M_PI;
	   return degTheta;
	}
}

class Timer
{
public :

	Timer()
		: lastTime(glfwGetTime())
	{
	}

	double getFrameTime()
	{ 
		const double current_time = glfwGetTime();
		const double delta = current_time - lastTime;

		lastTime = current_time;
		return delta;
	}

private :

	double lastTime;
};

class Vehicle
{
public :

	void Render();
};

void Vehicle::Render()
{
	glPushMatrix();

	const GLfloat body_width = 10;
	const GLfloat body_height = 25;

	const GLfloat tire_width = 2;
	const GLfloat tire_height = 5;

	// Body
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_QUADS);
		glVertex2f(-body_width, -body_height);
		glVertex2f( body_width, -body_height);
		glVertex2f( body_width,  body_height);
		glVertex2f(-body_width,  body_height);
	glEnd();

	const GLfloat offsetWidths[] =
	{
		body_width*0.9f - tire_width,
		body_width*0.9f - tire_width,

		-body_width*0.9f + tire_width,
		-body_width*0.9f + tire_width
	};

	const GLfloat offsetHeights[] =
	{
		body_height - tire_height,
		-body_height + tire_height,
		
		body_height - tire_height,
		-body_height + tire_height,
	};

	for( int i = 0; i < 4; ++i )
	{
		glPushMatrix();
			glTranslatef(offsetWidths[i], offsetHeights[i], 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_QUADS);
				glVertex2f(-tire_width, -tire_height);
				glVertex2f( tire_width, -tire_height);
				glVertex2f( tire_width,  tire_height);
				glVertex2f(-tire_width,  tire_height);
			glEnd();

		glPopMatrix();
	}

	glPopMatrix();
}
	

void GLFWCALL reshape( int w, int h )
{
   glViewport( 0, 0, (GLsizei)w, (GLsizei)h );

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluOrtho2D(-w/2, w/2, -h/2, h/2);
}


int main( void )
{
	bool running = true;

	// Initialize GLFW
	glfwInit();

	// Open an OpenGL window
	if( !glfwOpenWindow( 300,300, 0,0,0,0,0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		return 0;
	}

	glfwSetWindowTitle( "Vehicle Test Bed" );
	glfwSetWindowSizeCallback( reshape );
	glfwEnable( GLFW_STICKY_KEYS );
	//glfwSwapInterval( 1 );
	//glfwSetTime( 0.0 );

	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	//glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	//glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	//glEnable(GL_CULL_FACE);

	// Keep keys active until they are checked.
	glfwEnable( GLFW_STICKY_KEYS );

	Timer gameTime;
	Vehicle vehicle;

	// Main loop
	while( running )
	{
		// OpenGL rendering goes here...
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		vehicle.Render();

		// Swap front and back rendering buffers
		glfwSwapBuffers();

		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
			glfwGetWindowParam( GLFW_OPENED );
	}
	
	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	return 0;
}