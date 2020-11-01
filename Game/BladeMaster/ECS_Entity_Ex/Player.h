#pragma once
#include <memory>
class PlayerInputComponent;

class Player {
	int entityID;
	std::shared_ptr<PlayerInputComponent> inputComponent;
};