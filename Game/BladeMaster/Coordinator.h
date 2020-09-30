#pragma once
#include "ComponentManager.h"
#include "SystemManager.h"
#include "EntityManager.h"
class Coordinator
{
public:
	Coordinator() {
		mComponentManager = std::make_unique< ComponentManager>();
		mSystemManager = std::make_unique< SystemManager>();
		mEntityManager = std::make_unique< EntityManager>();
	}

	EntityID CreateEntity() {
		return mEntityManager->CreateEntity();
	}
	void DestroyEntity(EntityID entityID) {
		mEntityManager->DestroyEntity(entityID);
		mComponentManager->EntityDestroyed(entityID);
		mSystemManager->EntityDestroyed(entityID);
	}

	template<typename T>
	void AddComponent(EntityID entityID, T component ,ComponentType componentType) {
		//Turn on the bitset
		Bitmask bit = mEntityManager->GetBitmask(entityID);
		bit.set((int)componentType, true);
		mEntityManager->SetBitmask(entityID, bit);

		//add to array
		mComponentManager->AddComponent<T>(entityID, component, componentType);
	}
	template<typename T>
	void RemoveComponent(EntityID entityID, ComponentType componentType) {
		mComponentManager->RemoveComponent(entityID, componentType);

		Bitmask bit = mEntityManager->GetBitmask(entityID);
		bit.set((int)componentType, false);
		mEntityManager->SetBitmask(entityID, bit);
	}

	template<typename T>
	T& GetComponent(EntityID entityID, ComponentType componentType)
	{
		return mComponentManager->GetComponent<T>(entityID, componentType);
	}

	Bitmask GetEntityBitmask(EntityID entityID) {
		return mEntityManager->GetBitmask(entityID);
	}

	template<typename T>
	std::shared_ptr<T> GetSystem(SystemType systemType) {
		std::shared_ptr<SystemBase> ptr = mSystemManager->GetSystem<T>(systemType);
		return std::static_pointer_cast<T>(ptr);
	}
private:
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<SystemManager> mSystemManager;
	std::unique_ptr<EntityManager> mEntityManager;
};

