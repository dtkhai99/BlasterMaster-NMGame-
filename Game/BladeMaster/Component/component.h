#pragma once
#include <d3d9.h>
#include <d3dx9.h>

struct Sprite {
	LPDIRECT3DTEXTURE9 texture;
	LPCWSTR texturePath;
};

struct Position {
	float x;
	float y;
};