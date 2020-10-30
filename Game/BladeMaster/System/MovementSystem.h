#pragma once
#include "../Core/SystemBase.h"
#include <d3d9.h>
/*

*/

class CollisionEvent;

class MovementSystem : public SystemBase {
public:
	MovementSystem();
	void onEvent(const CollisionEvent*);
	void Update(DWORD dt);


};