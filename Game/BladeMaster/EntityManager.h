#pragma once
#include"Type.h"
#include<queue>
#include<array>



class EntityManager
{
public:
	EntityManager();
	~EntityManager() {};
	
	/*
	*	Basic CRUD function for entity
	*/
	EntityID CreateEntity();
	void DestroyEntity(EntityID);
	//Modify Entity's Content
	void SetBitmask(EntityID, Bitmask);
	//Read Entity's Content
	Bitmask GetBitmask(EntityID);


private:
	std::queue<EntityID> mAvailableIDs;
	std::array<Bitmask, MAX_ENTITIES> mEntityData;

	unsigned int mLivingEntityCounter;
};

