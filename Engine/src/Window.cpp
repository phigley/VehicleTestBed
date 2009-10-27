#include "Engine/Window.h"

#include <GL/glfw.h>

namespace
{
	void GLFWCALL reshape( int w, int h )
	{
	   glViewport( 0, 0, (GLsizei)w, (GLsizei)h );

	   glMatrixMode( GL_PROJECTION );
	   glLoadIdentity();
	   gluOrtho2D(-w/2, w/2, -h/2, h/2);
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
