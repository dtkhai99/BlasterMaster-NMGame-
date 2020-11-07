#include "SpriteDatabase.h"
#include "Debug.h"
#include "TextureDatabase.h"

void SpriteDatabase::AddSprite(short textureID)
{
	/*SpriteData spritedata;

	spritedata.area.left = rect.left;
	spritedata.area.top = rect.top;
	spritedata.area.right = rect.right;
	spritedata.area.bottom = rect.bottom;

	mSpriteData[textureID].push_back(spritedata);	*/

	TextureDatabase* textureDb = TextureDatabase::GetInstance();
	std::shared_ptr<TextureData> texture = textureDb->GetTexture(textureID);
	std::vector<SpriteData> sprites;
	for (int i = 0; i < texture->rows; i++)
	{
		for (int j = 0; j < texture->columns; j++)
		{
			SpriteData rect;
			rect.area.left = j * texture->size_width;
			rect.area.top = i * texture->size_height;
			rect.area.right = j * texture->size_width + texture->size_width;
			rect.area.bottom = i * texture->size_height + texture->size_height;

			sprites.push_back(rect);
		}
	}

	mSpriteData.emplace(textureID, sprites);

	mSpriteData.emplace(textureID, sprites);
}

SpriteDatabase* SpriteDatabase::__instance = NULL;
SpriteDatabase* SpriteDatabase::GetInstance()
{
	if (__instance == NULL) __instance = new SpriteDatabase();
	return __instance;
}

RECT SpriteDatabase::getSprite(short textureID, unsigned int spriteID) {
	if(mSpriteData.find(textureID) != mSpriteData.end()) {
		return mSpriteData.at(textureID)[spriteID].area;
	}
	DebugOut(L"Can't find texture id %d ",textureID);
	return RECT();
}

