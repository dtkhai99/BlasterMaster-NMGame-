#include "GraphicSystem.h"
#include "../Engine.h"
#include "../Core/Coordinator.h"
#include"../Component/SpriteComponent.h"
#include "../Component/PositionComponent.h"
#include "../TextureDatabase.h"
#include "../Component/AnimationComponent.h"
#include "../SpriteDatabase.h"
#include <thread>

extern Coordinator coordinator;

GraphicSystem::GraphicSystem()
{
	Bitmask requirement;
	requirement.set((int)ComponentType::Position, true);
	requirement.set((int)ComponentType::Sprite, true);
	mRequiredComponents.push_back(requirement);
	requirement.reset();
	requirement.set((int)ComponentType::Animation, true);
	requirement.set((int)ComponentType::Position, true);
	mRequiredComponents.push_back(requirement);
}

void GraphicSystem::SpriteRender()
{
	LPD3DXSPRITE spriteHandler = Engine::GetInstance()->GetSpriteHandler();
	TextureDatabase* textureDb = TextureDatabase::GetInstance();
	SpriteDatabase* spriteDb = SpriteDatabase::GetInstance();
	for (EntityID const& entity : mEntityList) {
		//Check if this entity has Animation component
		if ((coordinator.GetEntityBitmask(entity) & mRequiredComponents[1]) != mRequiredComponents[0]) continue;

		Sprite& sprite = coordinator.GetComponent<Sprite>(entity, ComponentType::Sprite);
		Position& position = coordinator.GetComponent<Position>(entity, ComponentType::Position);
		std::shared_ptr<TextureData> texture = textureDb->GetTexture((TextureID)sprite.textureID);
		RECT r = spriteDb->GetSprite(sprite.textureID, sprite.spriteID);
		D3DXVECTOR3 p(position.x, position.y, 0);

		spriteHandler->Draw(texture->texture, &r , NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	}
	
}

void GraphicSystem::AnimationRender()
{
	LPD3DXSPRITE spriteHandler = Engine::GetInstance()->GetSpriteHandler();
	TextureDatabase* textureDb = TextureDatabase::GetInstance();
	for (EntityID const& entity : mEntityList) {
		//Check if this entity has Animation component
		if ((coordinator.GetEntityBitmask(entity) & mRequiredComponents[1]) != mRequiredComponents[1]) continue;

		Animation& animation = coordinator.GetComponent<Animation>(entity, ComponentType::Animation);
		Position& position = coordinator.GetComponent<Position>(entity, ComponentType::Position);
		std::shared_ptr<TextureData> texture = textureDb->GetTexture((TextureID)animation.textureID);
		D3DXVECTOR3 p(position.x, position.y, 0);
		RECT r;
		r.left = animation.currentFrame % texture->columns * texture->size_width;
		r.top = animation.currentFrame % texture->rows * texture->size_height;
		r.right = animation.currentFrame % texture->columns * texture->size_width + texture->size_width;
		r.bottom = animation.currentFrame % texture->rows * texture->size_height + texture->size_height;
		spriteHandler->Draw(texture->texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void GraphicSystem::Update()
{
	DWORD now = GetTickCount();
	for (EntityID const& entity : mEntityList) {
		//Check if this entity has Animation component
		if ((coordinator.GetEntityBitmask(entity) & mRequiredComponents[1]) != mRequiredComponents[1]) continue;
		Animation& animation = coordinator.GetComponent<Animation>(entity, ComponentType::Animation);

		if (now - animation.animationCounter > animation.delayValue && animation.isFinished == false) {
			animation.currentFrame++;
			animation.animationCounter = now;
			if (animation.currentFrame == animation.stateDictionary[animation.currentState].endFrame + 1) {
				if (animation.stateDictionary[animation.currentState].isLoopable) {
					animation.currentFrame = animation.stateDictionary[animation.currentState].startFrame;
				}
				else {
					animation.isFinished = true;
					animation.currentState = StateID::Idle;
				}

			}
		}


	}
}
