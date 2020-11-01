#pragma once
#include"EventBase.h"
#include <vector>
/*
	This is some kind like a message sent to other system to handle when a collision happened
*/

//Forward declaration
struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

class CollisionEvent : public Event {
public:
	CollisionEvent(float min_tx, float min_ty, float nx, float ny, std::vector<LPCOLLISIONEVENT> & coEventResult, int entityID);

public:
	int entityID;
	float min_tx, min_ty, nx, ny;
	std::vector<LPCOLLISIONEVENT> coEventResult;
};