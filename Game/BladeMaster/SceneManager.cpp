#include "SceneManager.h"
#include "SceneBase.h"
SceneManager * SceneManager::__instance = NULL;

SceneManager::SceneManager()
{
}

void SceneManager::AddScene(SceneID id)
{

}

void SceneManager::SwapScene(SceneID swapedID, SceneID swappingID)
{
    //find the scene
    for (int i = 0; i < mCurrentScenes.size(); i++) {
        if (mCurrentScenes[i]->id == swapedID) {
            //SceneBase* scene = mScenesDatabase[swappingID]();
        }
    }
}

void SceneManager::RemoveScene(SceneID id)
{
}

void SceneManager::RemoveAllScene()
{
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
