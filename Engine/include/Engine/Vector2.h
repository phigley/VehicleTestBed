/*
 * Vector2.h
 *
 *  Created on: Oct 13, 2009
 *      Author: peterhigley
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <math.h>
namespace Engine
{
	struct Vector2
	{
		static Vector2 Empty;

		float x;
		float y;

		Vector2()
			: x(0.0f)
			, y(0.0f) {}

		Vector2(float my_x, float my_y)
			: x(my_x)
			, y(my_y) {}

		float dot(const Vector2& rhs) const
		{
			return x*rhs.x  + y*rhs.y;
		}

		float cross(const Vector2& rhs) const
		{
			return x*rhs.y - y*rhs.x;
		}

		float magSqr() const
		{
			return x*x + y*y;
		}

		float mag() const
		{
			return sqrtf(x*x + y*y);
		}

		float distanceTo(const Vector2& rhs) const
		{
			const float dx = x - rhs.x;
			const float dy = y - rhs.y;

			return sqrtf(dx*dx + dy*dy);
		}

		Vector2 rotatedBy(float angle) const
		{
			const float cs = cosf(angle);
			const float sn = sinf(angle);

			return Vector2( cs*x - sn*y, sn*x + cs*y );
		}

		Vector2& operator+=(const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
	};

	inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		Vector2 result = lhs;
		result += rhs;
		return result;
	}

	inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}


	inline Vector2 operator*(const Vector2& lhs, float scale)
	{
		return Vector2(lhs.x*scale, lhs.y*scale);
	}

	inline Vector2 operator/(const Vector2& lhs, float invScale)
	{
		// No check for division by zero!
		return Vector2(lhs.x/invScale, lhs.y/invScale);
	}

	inline bool operator==(const Vector2& lhs, const Vector2& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
}

#endif /* VECTOR2_H_ */
