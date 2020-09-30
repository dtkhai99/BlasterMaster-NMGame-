#include "System.h"
#include "Engine.h"
#include "Coordinator.h"
#include"component.h"

extern Coordinator coordinator;

GraphicSystem::GraphicSystem()
{
	Bitmask requirement;
	requirement.set((int)ComponentType::Position, true);
	requirement.set((int)ComponentType::Sprite, true);
	mRequiredComponents.push_back(requirement);
}
void GraphicSystem::LoadTexture()
{
	for (EntityID const& entity : mEntityList) {
		Sprite& sprite = coordinator.GetComponent<Sprite>(entity, ComponentType::Sprite);

		//Load Texture
		D3DXIMAGE_INFO info;
		HRESULT result = D3DXGetImageInfoFromFile(sprite.texturePath, &info);
		if (result != D3D_OK)
		{
			DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", sprite.texturePath);
			return;
		}

		LPDIRECT3DDEVICE9 d3ddv = Engine::GetInstance()->GetDirect3DDevice();

		result = D3DXCreateTextureFromFileEx(
			d3ddv,								// Pointer to Direct3D device object
			sprite.texturePath,						// Path to the image to load
			info.Width,							// Texture width
			info.Height,						// Texture height
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
			&info,
			NULL,
			&sprite.texture);								// Created texture pointer

		if (result != D3D_OK)
		{
			DebugOut(L"[ERROR] CreateTextureFromFile failed. File: %s\n", sprite.texturePath);
			return;
		}

		DebugOut(L"[INFO] Texture loaded Ok: %s \n", sprite.texturePath);
	}
}
void GraphicSystem::Render()
{
	LPD3DXSPRITE spriteHandler = Engine::GetInstance()->GetSpriteHandler();
	for (EntityID const& entity : mEntityList) {
		Sprite& sprite = coordinator.GetComponent<Sprite>(entity, ComponentType::Sprite);
		Position & position = coordinator.GetComponent<Position>(entity, ComponentType::Position);
		D3DXVECTOR3 p(position.x, position.y, 0);
		spriteHandler->Draw(sprite.texture, NULL, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	}

}
