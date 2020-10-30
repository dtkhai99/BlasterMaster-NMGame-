#include "PhysicEvent.h"

CollisionEvent::CollisionEvent(
	float min_tx, float min_ty, float nx, float ny, 
	std::vector<LPCOLLISIONEVENT>& coEventResult, 
	int entityID)
{
	this->min_tx = min_tx;
	this->min_ty = min_ty;
	this->nx = nx;
	this->ny = ny;
	this->coEventResult = coEventResult;
	this->entityID = entityID;
}
