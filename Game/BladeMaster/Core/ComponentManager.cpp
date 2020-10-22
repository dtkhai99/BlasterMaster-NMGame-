#include "ComponentManager.h"
#include"../Component/component.h"
ComponentManager::ComponentManager()
{
	RegisterComponent<Sprite>(ComponentType::Sprite);
	RegisterComponent<Position>(ComponentType::Position);
	RegisterComponent<SpritePos>(ComponentType::SpritePos);
}
