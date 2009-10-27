#include "Engine/Shape.h"
#include "Engine/Color.h"

#include <GL/glfw.h>

void Engine::Rectangle::Draw(float width, float height, const Color& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
		glVertex2f(-width, -height);
		glVertex2f( width, -height);
		glVertex2f( width,  height);
		glVertex2f(-width,  height);
	glEnd();
}