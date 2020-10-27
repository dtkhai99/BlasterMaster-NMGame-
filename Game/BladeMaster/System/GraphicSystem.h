#pragma once
#include "../Core/SystemBase.h"
#include <d3d9.h>
#include <d3dx9.h>

//This is a system belong to ECS
/*
	This system is supposed to render everything related to graphic
	It can render sprite and animation
	I want it render sprite and animation in two different function (It may has some duplicate code but that some thing to worry later)
	For an entity to be qualified to use this system, it must have:
		-> sprite component or animation component

	If an entity has animation, it must knows which animations are active,
	and iterates over these on each update cycle. For each active animation, it does various checks to
	determine whether the frame index should be incremented, or if the frame needs to be repeated. When an animation has completed,
	it checks if it is a looping animation, and if so, resets the frame index to 0 for that animation.
	Otherwise, it deactivates the animation and fires off an event so that any other systems that care about it find out.
	If there are no system care about deactivation of animation, this system will set entity back to default sprite

	Because an entity may have many sprites and animations, an entity is allowed to render one thing (either 1 sprite or 1 animation).
	If it is an animation, that animation must be finished before the system change to other sprite or animation
*/
class GraphicSystem : public SystemBase {
public:
	GraphicSystem();
	void Render();
};
