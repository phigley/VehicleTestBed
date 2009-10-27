#ifndef MATRIX2BLOCK_H_
#define MATRIX2BLOCK_H_

#include <GL/glfw.h>

namespace Engine
{
	class Matrix2Block
	{
	public :

		Matrix2Block(const Vector2& translation, float rotation = 0.0f)
		{
			glPushMatrix();

			// TODO : Use a matrix so that you don't have to convert to degrees.
			glRotatef(rotation * 180.0f / float(M_PI), 0.0f, 0.0f, 1.0f);
			glTranslatef(translation.x, translation.y, 0.0f);
		}

		~Matrix2Block()
		{
			glPopMatrix();
		}
	};
}

#endif // MATRIX2BLOCK_H_