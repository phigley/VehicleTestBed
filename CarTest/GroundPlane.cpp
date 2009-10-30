#include "GroundPlane.h"
#include "Engine.h"

GroundPlane::GroundPlane(float grid_size, const Engine::Color &color1_, const Engine::Color &color2_)
	: halfGridSize(grid_size/2.0f)
	, color1(color1_)
	, color2(color2_)
{
}

void GroundPlane::render(const Engine::Window& window)
{
	Engine::Vector2 projectionSize = window.getProjectionSize();

	const float limitX = (floorf(projectionSize.x/halfGridSize))*halfGridSize;
	const float limitY = (floorf(projectionSize.y/halfGridSize))*halfGridSize;

	bool rowToggle = false;
	for(float x = -limitX; x < limitX; x += 2*halfGridSize)
	{
		bool colorToggle = rowToggle;
		for(float y = -limitY; y < limitY; y += 2*halfGridSize)
		{
			Engine::Matrix2Block matrixBlock(Engine::Vector2(x,y));

			Engine::Rectangle::Draw(halfGridSize, halfGridSize, colorToggle ? color1 : color2);

			colorToggle = !colorToggle;
		}

		rowToggle = !rowToggle;
	}
}
