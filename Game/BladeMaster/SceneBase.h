#pragma once
#include <d3d9.h>
/*
	A scene is almost like a separate program within our game. Thus,
	Each game scene or state must be able to handle things on its own

	Question: Can a scene have a coordinator?
*/
class SceneBase
{
public:
	virtual ~SceneBase() {}
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

public:
	short id;
};

