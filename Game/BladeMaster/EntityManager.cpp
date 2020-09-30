#include "EntityManager.h"
#include "Debug.h"
EntityManager::EntityManager()
{
	mLivingEntityCounter = 0;
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		mAvailableIDs.push(i);
	}
}

EntityID EntityManager::CreateEntity()
{
	if (mLivingEntityCounter >= MAX_ENTITIES) {
		DebugOut(L"Entity ID reached limit");
		return -1;
	}

	EntityID id = mAvailableIDs.front();
	mAvailableIDs.pop();
	mEntityData[id] = Bitmask(0);
	mLivingEntityCounter++;
	return id;
}

void EntityManager::DestroyEntity(EntityID id)
{
	if (id > MAX_ENTITIES) {
		DebugOut(L"Entity ID out of reach");
		return;
	}
	//Return bitset to 0
	mEntityData[id].reset();
	//Recycle this id
	mAvailableIDs.push(id);
	mLivingEntityCounter--;
}

void EntityManager::SetBitmask(EntityID id, Bitmask bit)
{
	mEntityData[id] = bit;
}

Bitmask EntityManager::GetBitmask(EntityID id)
{
	if (id > MAX_ENTITIES) {
		DebugOut(L"Entity ID out of reach");
		return Bitmask(-1);
	}
	return mEntityData[id];
}
