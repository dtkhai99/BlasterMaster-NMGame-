#include "Map_1_Background.h"
#include "../Core/Coordinator.h"
#include "../Component/PositionComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/AnimationComponent.h"
#include "../SpriteDatabase.h"
#include "../System/GraphicSystem.h"
#include "../TextureDatabase.h"
#include <fstream>
#include <iostream>


extern Coordinator coordinator;

Map_1_Background::Map_1_Background(short id)
{
    this->id = id;

	/*TextureDatabase* textureDb = TextureDatabase::GetInstance();
	textureDb->LoadTextureFromPath(GUNNER, 4, 1, L"Resources/Worms.png");

	std::shared_ptr<GraphicSystem> graphicSystem = coordinator.GetSystem<GraphicSystem>(SystemType::Graphic);

	Position posTile;
	Animation ani;
	gunner = coordinator.CreateEntity();
	posTile.x = 16;
	posTile.y = 16;
	coordinator.AddComponent(gunner, posTile, ComponentType::Position);

	ani.textureID = GUNNER;
	ani.delayValue = 1000;
	ani.isFinished = false;
	State goLeft;
	goLeft.endFrame = 1;
	goLeft.startFrame = 0;
	goLeft.isLoopable = true;

	State goRight;
	goRight.endFrame = 3;
	goRight.startFrame = 2;
	goRight.isLoopable = true;
	ani.stateDictionary.emplace(StateID::Go_Left, goLeft);
	ani.stateDictionary.emplace(StateID::Go_Right, goRight);
	ani.currentState = StateID::Go_Left;
	ani.currentFrame = 0;
	coordinator.AddComponent(gunner, ani, ComponentType::Animation);

	graphicSystem->AddEntity(gunner);*/
	
	TextureDatabase * textureDb = TextureDatabase::GetInstance();
	textureDb->LoadTextureFromPath(BRICK, 12, 12, L"lvl2_side.png");

	std::shared_ptr<GraphicSystem> graphicSystem = coordinator.GetSystem<GraphicSystem>(SystemType::Graphic);

	SpriteDatabase* spriteDb = SpriteDatabase::GetInstance();

	int count = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			spriteDb->AddSprite(BRICK);

			sp[count].textureID = BRICK;
			sp[count].spriteID = count;

			count++;
		}
	}

	int number;
	int tempcount = 0;
	Position posTile[17000];
	int rowNumber = 0;
	int colNumber = 0;

	std::ifstream inFile;

	inFile.open("lvl2_side_tilemap.txt");
	//inFile.open("test.txt");
	if (!inFile)
	{
		std::cout << "Unable to open file";
		exit(1);
	}

	while (inFile >> number)
	{

		tilemap[tempcount] = coordinator.CreateEntity();
		spriteTile[tempcount].textureID = BRICK;
		spriteTile[tempcount].spriteID = number;
		coordinator.AddComponent(tilemap[tempcount], spriteTile[tempcount], ComponentType::Sprite);

		posTile[tempcount].x = colNumber * 16;
		posTile[tempcount].y = rowNumber * 16;
		coordinator.AddComponent(tilemap[tempcount], posTile[tempcount], ComponentType::Position);
		graphicSystem->AddEntity(tilemap[tempcount]);
		colNumber++;

		tempcount++;

		if (colNumber == 129)
		{
			colNumber = 0;
			rowNumber++;
		}
	}

	inFile.close();

	
}

void Map_1_Background::Update(DWORD dt)
{
	std::shared_ptr<GraphicSystem> graphicSystem = coordinator.GetSystem<GraphicSystem>(SystemType::Graphic);
	graphicSystem->Update();
}

void Map_1_Background::Render()
{
	std::shared_ptr<GraphicSystem> graphicSystem = coordinator.GetSystem<GraphicSystem>(SystemType::Graphic);
	graphicSystem->SpriteRender();
}


