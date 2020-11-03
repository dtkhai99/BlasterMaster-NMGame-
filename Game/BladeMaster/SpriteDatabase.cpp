#include "SpriteDatabase.h"

void SpriteDatabase::AddSprite(TextureID textureID, RECT rect, unsigned int count)
{
	SpriteData spritedata;

	spritedata.SpriteID = textureID * 1000 + count;
	spritedata.area.left = rect.left;
	spritedata.area.top = rect.top;
	spritedata.area.right = rect.right;
	spritedata.area.bottom = rect.bottom;

	mSpriteData[textureID].push_back(spritedata);

}

SpriteDatabase* SpriteDatabase::__instance = NULL;
SpriteDatabase* SpriteDatabase::GetInstance()
{
	if (__instance == NULL) __instance = new SpriteDatabase();
	return __instance;
}

int SpriteDatabase::GetSpriteID(unsigned int id)
{
	for (auto& ell : mSpriteData)
	{
		for (auto& ell2 : ell.second)
		{
			if (ell2.SpriteID == id)
			{
				return ell2.SpriteID;
			}
		}
	}
	
}

RECT SpriteDatabase::GetRECT(unsigned int id)
{
	for (auto& ell : mSpriteData)
	{
		for (auto& ell2 : ell.second)
		{
			if (ell2.SpriteID == id)
			{
				return ell2.area;
			}
		}
	}
}
