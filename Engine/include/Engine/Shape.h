#ifndef SHAPE_H_
#define SHAPE_H_

#include <GL/glfw.h>

namespace Engine
{
	struct Color;

	namespace Rectangle
	{
		void Draw(float width, float height, const Color& color);
	}
}

#endif // SHAPE_H_