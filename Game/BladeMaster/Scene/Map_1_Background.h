#pragma once
#include "SceneBase.h"
/*
	This class's sole purepose is render background of world 1
*/
class Map_1_Background : public SceneBase {
public:
	Map_1_Background(){}
	Map_1_Background(short id);
	// Inherited via SceneBase
	virtual void Update(DWORD dt) override;
	virtual void Render() override;

private:
	//int tilemap[17000];
	//int tileset[150];
	int gunner;
};