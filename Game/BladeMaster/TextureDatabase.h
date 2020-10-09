#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <unordered_map>
#include <memory>

// Map texture id to something meaningful
enum class TextureType {
	Brick = 0,
};

// This class will load texture data (texture path)
// To container and Graphic System (or some high-level system) will reference to
// content of this database
class TextureDatabase
{
public:
	void ReadData(LPCWSTR path);
	std::shared_ptr<LPDIRECT3DTEXTURE9> GetTexture(TextureType type);

private:
	std::unordered_map<TextureType, std::shared_ptr<LPDIRECT3DTEXTURE9>> mDatabase;
};

