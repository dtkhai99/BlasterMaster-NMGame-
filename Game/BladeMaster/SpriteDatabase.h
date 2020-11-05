#pragma once
#include <map>
#include <vector>
#include <d3d9.h>
/*
						|	index | left  | top  |  right  |  bottom  |
				mapping	|	 1	  |	16	|	0  |	16	 |	16		|
	texture id-------->	|	 2	  |	32	|	0  |	16	 |	16		|
						|	 ..   | ..	|		|	   |		 |			|

						left, top, right, bottom group as Rect
						Should there be a TextureID	between SpriteID and Rect?


	these left, top, right, bottom can be group as RECT struct of directX
	index can be used as index of vector

	Question: Should it be use for animation?
*/
struct SpriteData {
	RECT area;
};
class SpriteDatabase
{
public:
	void AddSprite(short textureID);
	static SpriteDatabase* GetInstance();
	RECT GetSprite(short textureID,unsigned int spriteID);
private:
	std::map<short, std::vector<SpriteData>> mSpriteData;
	static SpriteDatabase* __instance;
};
