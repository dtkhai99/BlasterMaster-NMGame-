#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <unordered_map>
#include <memory>

// This is just a table in database
/*
	|-----------------------------------|----------------------------|-------------
	|	Texture Id	|	Texture data	|	columns		|	rows	 |	 size	|
	|---------------|-------------------|---------------|------------|----------|
	|		1		| LPDIRECT3DTEXTURE9|		5		|	  6		 |	 32		|
	|		.		|		..			|		..		|	  .		 |			|
	|		.		|		..			|		..		|	  .		 |			|
	|---------------|-------------------|---------------|------------|----------|

	Every texture file's path will be store in txt file and this class will load them to LPDIRECT3DTEXTURE9 type
	of directx 9. No one outside this class will store Texture data, only store Texture id.

	This class may load a texture from specific path (not recommended - it should be for test only)

	There will be only 1 texture database in the game
*/
// Map texture id to something meaningful
enum class TextureID {
	Brick = 0,
};

struct TextureData {
	LPDIRECT3DTEXTURE9 texture;
	unsigned int columns;
	unsigned int rows;
	unsigned int size;
};
class TextureDatabase
{
public:
	void ReadDataFromFile(LPCWSTR path);
	void LoadTextureFromPath(TextureID id, 
							unsigned int columns, 
							unsigned int rows, 
							unsigned int size, 
							LPCWSTR texturePath);
	std::shared_ptr<TextureData> GetTexture(TextureID id);
	static TextureDatabase* GetInstance();
private:
	std::unordered_map<TextureID, std::shared_ptr<TextureData>> mDatabase;
	static TextureDatabase* __instance;
};

