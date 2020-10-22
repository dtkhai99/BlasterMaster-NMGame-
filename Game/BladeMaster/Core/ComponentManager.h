#pragma once
#include "ComponentArray.h"
#include<memory>
enum class ComponentType {
	Sprite = 0,
	Position,
	SpritePos
};

class ComponentManager
{
public:
	ComponentManager();
	template<typename T>
	void RegisterComponent(ComponentType componentType) {
		if (mComponentArray.find(componentType) != mComponentArray.end()) {
			DebugOut(L"This component type has registered");
			return;
		}
		mComponentArray.insert({ componentType , std::make_shared<ComponentArray<T>>() });
	}

	template<typename T>
	void AddComponent(EntityID entityID,T component, ComponentType componentType) {
		if (mComponentArray.find(componentType) == mComponentArray.end()) {
			DebugOut(L"This component type not registered");
			return;
		}

		GetComponentArray<T>(componentType)->InsertData(entityID, component);
	}

	template<typename T>
	void RemoveComponent(EntityID entityID, ComponentType componentType) {
		if (mComponentArray.find(componentType) == mComponentArray.end()) {
			DebugOut(L"This component type not registered");
			return nullptr;
		}

		GetComponentArray<T>(componentType)->RemoveData(entityID);
	}

	template<typename T>
	T& GetComponent(EntityID entityID, ComponentType componentType) {
		if (mComponentArray.find(componentType) == mComponentArray.end()) {
			DebugOut(L"This component type not registered");
			return T();
		}

		return GetComponentArray<T>(componentType)->GetData(entityID);
	}

	void EntityDestroyed(EntityID entityID) {
		for (auto const& iterator : mComponentArray) {
			std::shared_ptr<IComponentArray> const& componentArray = iterator.second;
			componentArray->EntityDestroyed(entityID);
		}
	}

private: /*Helper function*/

	// Casting IComponentArray pointer to ComponentArray pointer
	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray(ComponentType componentType){
		if (mComponentArray.find(componentType) == mComponentArray.end()) {
			DebugOut(L"This component type not registered");
			return nullptr;
		}
		return std::static_pointer_cast<ComponentArray<T>>(mComponentArray[componentType]);
	}

private: /*Data*/
	std::unordered_map<ComponentType, std::shared_ptr<IComponentArray>> mComponentArray{};

};

