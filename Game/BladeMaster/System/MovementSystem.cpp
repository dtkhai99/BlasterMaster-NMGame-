#include "MovementSystem.h"
#include "../Core/Coordinator.h"
#include "../EventHandler/PhysicEvent.h"
#include "../Component/PositionComponent.h"
#include "../Component/SpeedComponent.h"
extern Coordinator coordinator;
MovementSystem::MovementSystem()
{
	Bitmask requirement;
	requirement.set((int)ComponentType::Speed, true);
	requirement.set((int)ComponentType::Position, true);
	mRequiredComponents.push_back(requirement);
}

void MovementSystem::onEvent(const CollisionEvent * _event)
{
	Position& pos = coordinator.GetComponent<Position>(_event->entityID, ComponentType::Position);
	Velocity & speed = coordinator.GetComponent<Velocity>(_event->entityID, ComponentType::Speed);


	// block every object first!
	pos.x += _event->min_tx * speed.dx + _event->nx * 0.4f;
	pos.y += _event->min_ty * speed.dy + _event->ny * 0.4f;

	if (_event->nx != 0) speed.vx = 0;
	if (_event->ny != 0) speed.vy = 0;

	for (UINT i = 0; i < _event->coEventResult.size(); i++) {

	}
}

void MovementSystem::Update(DWORD dt)
{
	for (EntityID const & entity : mEntityList) {
		Position& pos = coordinator.GetComponent<Position>(entity, ComponentType::Position);
		Velocity& speed = coordinator.GetComponent<Velocity>(entity, ComponentType::Speed);
		speed.dx = speed.vx * dt;
		speed.dy = speed.vy * dt;

		pos.x += speed.dx;
		pos.y += speed.dy;
	}
}
