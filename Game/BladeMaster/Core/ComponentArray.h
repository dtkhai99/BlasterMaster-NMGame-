#pragma once
#include"Type.h"
#include"../Debug.h"
#include<array>
#include<unordered_map>

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(EntityID entityID) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray{
public:
	void InsertData(EntityID entityID, T component) {
		if (mSparse.find(entityID) != mSparse.end()) {
			DebugOut(L"Entity already exists");
			return;
		}

		std::pair<EntityID, T> pair = std::make_pair(entityID, component);
		mComponentArray[mCounter] = pair;
		mSparse[entityID] = mCounter;
		mCounter++;
	}

	void RemoveData(EntityID entityID) {
		if (mSparse.find(entityID) == mSparse.end()) {
			DebugOut(L"Entity is not exists");
			return;
		}
		
		std::pair<EntityID, T> temp = mComponentArray[mCounter - 1];
		mComponentArray[mSparse[entityID]] = temp;
		mSparse[temp.first] = mSparse[entityID];
		mSparse.erase(entityID);
	}

	T& GetData(EntityID entityID) {
		if (mSparse.find(entityID) == mSparse.end()) {
			DebugOut(L"Entity is not exists");
			return T();
		}

		return mComponentArray[mSparse[entityID]].second;
	}

	void EntityDestroyed(EntityID entityID) {
		if (mSparse.find(entityID) != mSparse.end()) {
			RemoveData(entityID);
		}
	}
private:
	//Using Sparse set -- Must know sparse set to understand this
	std::array<std::pair<EntityID, T>, MAX_ENTITIES> mComponentArray;
	std::unordered_map<int, int> mSparse;
	unsigned int mCounter = 0;													//Count amounts of component in this array
	
};