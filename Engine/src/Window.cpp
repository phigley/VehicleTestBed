#include "Engine/Window.h"

#include <GL/glfw.h>

namespace
{
	// It would be nice t move these into Window.
	// But glfw does not support multiple windows,
	// hence it does not have user-data associated with
	// its reshape callback.
	double projectionWidth = 1.0;
	double projectionHeight = 1.0;

	void GLFWCALL reshape( int w, int h )
	{
	   glViewport( 0, 0, (GLsizei)w, (GLsizei)h );

		double adjustedProjectionWidth = projectionWidth;
		double adjsutedProjectionHeight = projectionHeight;

		// w/pw > h/ph
		if (double(w)*projectionHeight >= double(h)*projectionWidth)
		{
			adjustedProjectionWidth = double(w)/double(h)*projectionHeight;
		}
		else
		{
			adjsutedProjectionHeight = double(h)/double(w)*projectionWidth;
		}

	   glMatrixMode( GL_PROJECTION );
	   glLoadIdentity();
	   gluOrtho2D(-adjustedProjectionWidth/2, adjustedProjectionWidth/2, -adjsutedProjectionHeight/2, adjsutedProjectionHeight/2);
	}
}

Engine::Window::Window(int width, int height, const char* title)
{
	// Initialize GLFW
	glfwInit();

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

	// Open an OpenGL window
	if( !glfwOpenWindow( width, height, 0,0,0,0,0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		return;
	}

	glfwSetWindowTitle( title );
	glfwSetWindowSizeCallback( reshape );

	// Tearing is ugly!
	glfwSwapInterval( 1 );

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	//glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	//glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

//	// Go ahead and enable these, although
//	// point will never be used.
//	glEnable(GL_POINT_SMOOTH);
//	glHint(GL_POINT_SMOOTH, GL_NICEST);
//	glEnable(GL_LINE_SMOOTH);
//	glHint(GL_LINE_SMOOTH, GL_NICEST);
//	glEnable(GL_POLYGON_SMOOTH);
//	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	// This probably doesn't matter, but it keeps me
	// honest about my vertex order!
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Keep keys active until they are checked.
	glfwEnable( GLFW_STICKY_KEYS );
}

Engine::Window::~Window()
{
	glfwTerminate();
}

void Engine::Window::setProjectionSize(float width, float height)
{
	// Store the new size.
	projectionWidth = width;
	projectionHeight = height;

	// Reshape the window.
	int w,h;
	glfwGetWindowSize(&w, &h);
	reshape(w,h);
}