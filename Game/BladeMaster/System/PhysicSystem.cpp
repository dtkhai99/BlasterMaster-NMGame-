#include"PhysicSystem.h"
#include "../Core/Coordinator.h"
#include "../Component/BoundingBoxComponent.h"
#include "../Component/SpeedComponent.h"
#include "../EventHandler/PhysicEvent.h"
#include "../EventHandler/EventHandling.h"
extern Coordinator coordinator;
extern EventHandling eventHandling;

PhysicSystem::PhysicSystem()
{
	Bitmask requirement;
	requirement.set((int)ComponentType::Speed);
	requirement.set((int)ComponentType::BoundingBox);
	mRequiredComponents.push_back(requirement);
}

void PhysicSystem::Update(DWORD dt)
{
	for (EntityID const& entity : mEntityList) {
		std::vector<LPCOLLISIONEVENT> coEvents;
		std::vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(entity, coEvents, dt);
		if (coEvents.size() != 0) {
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			CollisionEvent* collisionEvent = new CollisionEvent(min_tx, min_ty, nx, ny, coEventsResult, entity);
			eventHandling.handleEvent(collisionEvent);
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void PhysicSystem::CalcPotentialCollisions(EntityID staticID, std::vector<LPCOLLISIONEVENT>& coEvents, DWORD dt)
{
	for (EntityID const& entity : mEntityList) {
		if (staticID == entity) continue;
		LPCOLLISIONEVENT e = SweptAABBEx(entity, staticID, dt);

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void PhysicSystem::FilterCollision(
	std::vector<LPCOLLISIONEVENT>& coEvents, 
	std::vector<LPCOLLISIONEVENT>& coEventsResult, 
	float& min_tx, float& min_ty, 
	float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

LPCOLLISIONEVENT PhysicSystem::SweptAABBEx(EntityID movingID, EntityID staticID, DWORD dt)
{
	BoundingBox & staticObject = coordinator.GetComponent<BoundingBox>(staticID, ComponentType::BoundingBox);;
	BoundingBox & movingObject = coordinator.GetComponent<BoundingBox>(movingID, ComponentType::BoundingBox);
	Velocity& movingObjectSpeed = coordinator.GetComponent<Velocity>(movingID, ComponentType::Speed);
	Velocity & staticObjectSpeed = coordinator.GetComponent<Velocity>(staticID, ComponentType::Speed);
	float t, nx, ny;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = staticObjectSpeed.vx * dt - movingObjectSpeed.vx * dt;
	float rdy = staticObjectSpeed.vy * dt - movingObjectSpeed.vy * dt;

	SweptAABB(
		movingObject.left, movingObject.top, movingObject.right, movingObject.bottom,
		rdx, rdy,
		staticObject.left, staticObject.top, staticObject.right, staticObject.bottom,
		t, nx, ny
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, movingID);
	return e;
}

void PhysicSystem::SweptAABB(
	float ml, float mt, float mr, float mb, 
	float dx, float dy, 
	float sl, float st, float sr, float sb, 
	float& t, float& nx, float& ny)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -999999.0f;
		tx_exit = 999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999.0f;
		ty_exit = 99999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}
