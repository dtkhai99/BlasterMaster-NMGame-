#include "SystemManager.h"
#include "../System/GraphicSystem.h"
#include "../System/InputSystem.h"
SystemManager::SystemManager()
{
	mSystems.insert({ SystemType::Graphic, std::make_shared<GraphicSystem>() });
	mSystems.insert({ SystemType::Input, std::make_shared<InputSystem>() });

}
