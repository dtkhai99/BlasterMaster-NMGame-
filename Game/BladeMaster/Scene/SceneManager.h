#pragma once
#include <vector>
#include <map>
#include <d3d9.h>
#include <functional>
/*
	Approach 1:
	Our main goal is to create a scene manager with no limit to the number of elements and distinct elements it 
	can show and to provide an easy way to add new scenes. One way to ensure a working scene flow (allowing the 
	user to go back and forth between scenes) is to use a stack of scene.

	Another thing to consider is that sometimes multiple scenes must be visible. Thus when render, we will render
	from back to front of a stack (kinda like layers)

	For more information: https://bell0bytes.eu/scene-manager/

	Approach 2:
	Use Facade or Mediator design pattern
*/
using SceneID = short;
#define MAP_1 0

class SceneBase;
class SceneManager
{
public:
	/*
		For now this Scene Manager have too much responsibility. Need refactor it in future
	*/
	SceneManager();
	void AddScene(SceneID id);
	bool SwapScene(SceneID swapedID, SceneID swappingID);
	void RemoveScene(SceneID id);
	void RemoveAllScene();
	void Update(DWORD dt);
	void Render();

	static SceneManager * getInstance();

private: //Helper function
	SceneBase* createScene(SceneID id); //Use abstract factory pattern
private:
	std::vector<SceneBase*> mCurrentScenes;
	static SceneManager * __instance;
};

