#include "SystemManager.h"
#include "System.h"
SystemManager::SystemManager()
{
	mSystems.insert({ SystemType::Graphic, std::make_shared<GraphicSystem>() });
}
