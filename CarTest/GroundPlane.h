#ifndef GROUNDPLANE_H_
#define GROUNDPLANE_H_

#include "Engine/Color.h"
namespace Engine
{
	class Window;
}

class GroundPlane
{
public:

	GroundPlane(float grid_size, const Engine::Color& color1_, const Engine::Color& color2_);

	void render(const Engine::Window& window);

private:

	float halfGridSize;
	Engine::Color color1;
	Engine::Color color2;
};

#endif // GROUNDPLANE_H_

