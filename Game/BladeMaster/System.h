#pragma once
#include"SystemBase.h"
#include <d3d9.h>
#include <d3dx9.h>

class GraphicSystem : public SystemBase {
public:
	GraphicSystem();
	void LoadTexture();
	void Render();
};