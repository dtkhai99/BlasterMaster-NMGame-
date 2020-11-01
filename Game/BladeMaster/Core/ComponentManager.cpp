#include "ComponentManager.h"
#include"../Component/PositionComponent.h"
#include"../Component/SpriteComponent.h"
#include"../Component/AnimationComponent.h"

ComponentManager::ComponentManager()
{
	RegisterComponent<Sprite>(ComponentType::Sprite);
	RegisterComponent<Position>(ComponentType::Position);
	RegisterComponent<Animation>(ComponentType::Animation);
}
