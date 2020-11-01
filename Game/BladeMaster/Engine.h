#pragma once
#include"stdafx.h"
class Engine
{
public:
	Engine();
	~Engine();

	/*
	* Load Game resource
	*/
	void LoadResource();

	void InitDirectX(HWND hWnd);
	static Engine* GetInstance();
	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }
private:
	HWND hWnd;
	static Engine* __instance;
	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	int backBufferWidth = 0;
	int backBufferHeight = 0;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D images 


};

