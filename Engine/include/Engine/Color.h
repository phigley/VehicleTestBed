#ifndef COLOR_H_
#define COLOR_H_

#include <GL/glfw.h>

namespace Engine
{
	struct Color
	{
		float r;
		float g;
		float b;
		float a;

		Color(float red, float green, float blue, float alpha)
			: r(red)
			, g(green)
			, b(blue)
			, a(alpha)
		{
		}

		Color(const Color& src, float alpha)
			: r(src.r)
			, g(src.g)
			, b(src.b)
			, a(alpha)
		{
		}

		static const Color Red;
		static const Color Green;
		static const Color Blue;
	};
}

#endif // COLOR_H_