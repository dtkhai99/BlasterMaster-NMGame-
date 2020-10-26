#include "ComponentManager.h"
#include"../Component/PositionComponent.h"
#include"../Component/SpriteComponent.h"
ComponentManager::ComponentManager()
{
	RegisterComponent<Sprite>(ComponentType::Sprite);
	RegisterComponent<Position>(ComponentType::Position);
}
