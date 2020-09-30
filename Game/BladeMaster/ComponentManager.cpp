#include "ComponentManager.h"
#include"component.h"
ComponentManager::ComponentManager()
{
	RegisterComponent<Sprite>(ComponentType::Sprite);
	RegisterComponent<Position>(ComponentType::Position);
}
