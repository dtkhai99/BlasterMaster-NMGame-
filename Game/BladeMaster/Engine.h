#pragma once
#include"stdafx.h"

class Engine
{
public:
	Engine(HWND);
	~Engine();
	
	/*
		Update world status for this frame
		dt: time period between beginning of last frame and beginning of this frame

		IMPORTANT: no render-related code should be used inside this function.
	*/
	void Update(DWORD dt);
	
	/*
	* Load Game resource
	*/
	void LoadResource();

	/*
		Render a frame
		IMPORTANT: world status must NOT be changed during rendering
	*/
	void Render();


	void InitDirectX(HWND hWnd);

private:
	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	int BackBufferWidth = 0;
	int BackBufferHeight = 0;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D images 

	LPDIRECT3DTEXTURE9 texBrick;				// Texture object to store brick image

};

