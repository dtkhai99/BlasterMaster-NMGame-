#include "GraphicSystem.h"
#include "../Engine.h"
#include "../Core/Coordinator.h"
#include"../Component/SpriteComponent.h"
#include "../Component/PositionComponent.h"
#include "../TextureDatabase.h"
extern Coordinator coordinator;

GraphicSystem::GraphicSystem()
{
	Bitmask requirement;
	requirement.set((int)ComponentType::Position, true);
	requirement.set((int)ComponentType::Sprite, true);
	mRequiredComponents.push_back(requirement);
}

void GraphicSystem::Render()
{
	LPD3DXSPRITE spriteHandler = Engine::GetInstance()->GetSpriteHandler();
	TextureDatabase * textureDb = TextureDatabase::GetInstance();
	for (EntityID const& entity : mEntityList) {
		Sprite& sprite = coordinator.GetComponent<Sprite>(entity, ComponentType::Sprite);
		Position & position = coordinator.GetComponent<Position>(entity, ComponentType::Position);
		std::shared_ptr<LPDIRECT3DTEXTURE9> texture = textureDb->GetTexture((TextureID)sprite.textureID);

		D3DXVECTOR3 p(position.x, position.y, 0);
		spriteHandler->Draw(*texture, &sprite.area, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	}

}
