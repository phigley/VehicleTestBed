#ifndef SHAPE_H_
#define SHAPE_H_

#include <GL/glfw.h>

namespace Engine
{
	struct Color;

	namespace Rectangle
	{
		void Draw(float halfWidth, float halfHeight, const Color& color);
	}
}

#endif // SHAPE_H_