#include "Engine.h"
#include "Debug.h"
Engine* Engine::__instance = NULL;

Engine::Engine()
{
	LoadResource();
}
Engine::~Engine()
{
	spriteHandler->Release();
	backBuffer->Release();
	d3ddv->Release();
	d3d->Release();

	DebugOut(L"[INFO] Cleanup Ok\n");
}

void Engine::LoadResource()
{
	
}


void Engine::InitDirectX(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->hWnd = hWnd;
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	// retrieve window width & height so that we can create backbuffer height & width accordingly 
	RECT r;
	GetClientRect(hWnd, &r);

	backBufferWidth = r.right + 1;
	backBufferHeight = r.bottom + 1;

	d3dpp.BackBufferHeight = backBufferHeight;
	d3dpp.BackBufferWidth = backBufferWidth;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,			// use default video card in the system, some systems have more than one video cards
		D3DDEVTYPE_HAL,				// HAL = Hardware Abstraction Layer - a "thin" software layer to allow application to directly interact with video card hardware
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		DebugOut(L"[ERROR] CreateDevice failed\n %s %d", __FILE__, __LINE__);
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	DebugOut(L"[INFO] InitDirectX OK\n");
}

Engine* Engine::GetInstance()
{
	if (__instance == NULL) __instance = new Engine();
	return __instance;
}
