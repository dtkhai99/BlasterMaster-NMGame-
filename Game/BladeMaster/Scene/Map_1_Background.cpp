#include "Map_1_Background.h"
#include "../Core/Coordinator.h"
#include "../Component/PositionComponent.h"
#include "../Component/SpriteComponent.h"
#include "../System/GraphicSystem.h"
#include "../TextureDatabase.h"
#include <fstream>
#include <iostream>

extern Coordinator coordinator;
Map_1_Background::Map_1_Background(short id)
{
    this->id = id;
	
	Sprite sp[150];
	TextureDatabase * textureDb = TextureDatabase::GetInstance();
	textureDb->LoadTextureFromPath(BRICK, 12, 12, 16, L"lvl2_side.png");

	std::shared_ptr<GraphicSystem> graphicSystem = coordinator.GetSystem<GraphicSystem>(SystemType::Graphic);

	int count = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			tileset[count] = coordinator.CreateEntity();


			sp[count].textureID = BRICK;
			sp[count].area.left = j * 16;
			sp[count].area.top = i * 16;
			sp[count].area.right = j * 16 + 16;
			sp[count].area.bottom = i * 16 + 16;
			coordinator.AddComponent(tileset[count], sp[count], ComponentType::Sprite);
			count++;
		}
	}

	int number;
	int tempcount = 0;
	Position posTile[17000];
	Sprite spriteTile[17000];
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
		for (int i = 0; i < 144; i++)
		{
			if (number == tileset[i])
			{
				tilemap[tempcount] = coordinator.CreateEntity();

				spriteTile[tempcount] = coordinator.GetComponent<Sprite>(tileset[i], ComponentType::Sprite);
				coordinator.AddComponent(tilemap[tempcount], spriteTile[tempcount], ComponentType::Sprite);

				posTile[tempcount].x = colNumber * 16;
				posTile[tempcount].y = rowNumber * 16;
				coordinator.AddComponent(tilemap[tempcount], posTile[tempcount], ComponentType::Position);
				graphicSystem->AddEntity(tilemap[tempcount]);
				colNumber++;

				tempcount++;



				break;
			}
		}
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
}

void Map_1_Background::Render()
{
	std::shared_ptr<GraphicSystem> graphicSystem = coordinator.GetSystem<GraphicSystem>(SystemType::Graphic);
	graphicSystem->SpriteRender();
}


