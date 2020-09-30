#pragma once
#include"Type.h"
#include<set>
#include<vector>

using Requirements = std::vector<Bitmask>;
class SystemBase
{
public:
	void AddEntity(EntityID);
	void RemoveEntity(EntityID);
public:
	std::set<EntityID> mEntityList;
	Requirements mRequiredComponents;
};

