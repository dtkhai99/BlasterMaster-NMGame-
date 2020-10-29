#include "../Core/SystemBase.h"

/*
	At this time, this system will implement sweepAABB techniques collision. 
	It will detect collision and fires off notification when this happen. 
	It won't handling any sequence when there is a collision

	To be qualified, an entity must have BoundingBoxComponent and SpeedComponent
*/
typedef unsigned long DWORD;
struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	EntityID obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, EntityID obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class PhysicSystem : public SystemBase {
public:
	PhysicSystem();
	void Update(DWORD dt);
	void CalcPotentialCollisions(EntityID staticID,std::vector<LPCOLLISIONEVENT>& coEvents, DWORD dt);
	void FilterCollision(
		std::vector<LPCOLLISIONEVENT>& coEvents,
		std::vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx, float& min_ty,
		float& nx, float& ny, float& rdx, float& rdy);
	LPCOLLISIONEVENT SweptAABBEx(EntityID movingId, EntityID staticID, DWORD dt);
private:
	void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float& t, float& nx, float& ny);

};