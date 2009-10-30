#include "Engine/Shape.h"
#include "Engine/Color.h"

#include <GL/glfw.h>

void Engine::Rectangle::Draw(float halfWidth, float halfHeight, const Color& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
		glVertex2f(-halfWidth, -halfHeight);
		glVertex2f( halfWidth, -halfHeight);
		glVertex2f( halfWidth,  halfHeight);
		glVertex2f(-halfWidth,  halfHeight);
	glEnd();
}