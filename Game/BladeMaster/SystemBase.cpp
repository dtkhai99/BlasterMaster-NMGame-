#include "SystemBase.h"
#include"Coordinator.h"

extern Coordinator coordinator;
void SystemBase::AddEntity(EntityID entityID)
{
	//Check entity bitmask whether it satisfy the requirement
	Bitmask entityBitmask = coordinator.GetEntityBitmask(entityID);
	if (std::find_if(mRequiredComponents.begin(), mRequiredComponents.end(), [entityBitmask](Bitmask& requirement) {
			if ((entityBitmask & requirement) == requirement) return true;
			return false;
		}) != mRequiredComponents.end()) {
		mEntityList.insert(entityID);
	}
}

void SystemBase::RemoveEntity(EntityID entityID)
{
	mEntityList.erase(entityID);
}
