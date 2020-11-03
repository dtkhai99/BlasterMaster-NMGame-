#include "SceneManager.h"
#include "SceneBase.h"
#include "../Debug.h"
#include "Map_1_Background.h"

SceneManager * SceneManager::__instance = NULL;

SceneManager::SceneManager()
{
    
}


void SceneManager::AddScene(SceneID id)
{
    SceneBase* newScene = createScene(id);
    mCurrentScenes.push_back(newScene);
}

//Error-prone. Need to test carefully
bool SceneManager::SwapScene(SceneID swapedID, SceneID swappingID)
{
    //find the scene
    for (int i = 0; i < mCurrentScenes.size(); i++) {
        if (mCurrentScenes[i]->getID() == swapedID) {
            SceneBase* newScene = createScene(swappingID);
            SceneBase* temp = mCurrentScenes[i];
            mCurrentScenes[i] = newScene;
            delete temp;
            return true;
        }
    }
    return false;
}

void SceneManager::RemoveScene(SceneID id)
{
    for (int i = 0; i < mCurrentScenes.size(); i++) {
        if (mCurrentScenes[i]->getID() == id)
            delete mCurrentScenes[i];
        //I'm not sure about this. Must testing carefully
        mCurrentScenes.erase(mCurrentScenes.begin() + i); 
        break;
    }
}

void SceneManager::RemoveAllScene()
{
    for (int i = 0; i < mCurrentScenes.size(); i++) {
        delete mCurrentScenes[i];
    }
}

void SceneManager::Update(DWORD dt)
{
    //Update from back to font
    for (int i = mCurrentScenes.size() - 1; i >= 0; i--) {
        mCurrentScenes[i]->Update(dt);
    }
}

void SceneManager::Render()
{
    //Render from back to font
    for (int i = mCurrentScenes.size() - 1; i >= 0; i--) {
        mCurrentScenes[i]->Render();
    }
}

SceneManager* SceneManager::getInstance()
{
    if (__instance == nullptr) __instance = new SceneManager();
    return __instance;
}

SceneBase* SceneManager::createScene(SceneID id)
{
    switch (id) {
    case MAP_1: return new Map_1_Background(MAP_1); break;

    default:
        DebugOut(L"Scene with id %d is defined", id);
    }
}
