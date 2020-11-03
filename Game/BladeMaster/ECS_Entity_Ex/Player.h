#pragma once
#include <memory>
class PlayerInputComponent;

class Player {
	Player();
	int entityID;
	std::shared_ptr<PlayerInputComponent> inputComponent;
};
