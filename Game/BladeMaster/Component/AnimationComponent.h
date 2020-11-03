#pragma once
#include<unordered_map>
#include<d3d9.h>
/*
	Any entity have more than 2 sprite needs to render will become animation.
	If that happened, we will distinguish sprites or sequence of sprites by states.
	At one specific moment, 1 entity is only at 1 state

	All sprites of an animation must be drawn in same texture file

	States are simply pairs of start and end frames with a Boolean value indicating whether the state is loopable .
	By storing states in a dictionary, it is easy to reference a specific state

	There is an integer representing the current frame of the sprite, two integers used as an animation counter
	and delay value to determine how often the sprite frame should change, and a Boolean
	value indicating whether a non-loopable state has completed its animation. This
	Boolean value can be used to prevent the sprite from changing in the middle of a
	specific animation. The animation counter is incremented each tick of the update loop,
	but the sprite frame is only changed once the animation counter reaches the animation
	delay value, at which point the animation counter is reset. Current state of animation
	must also be tracked
*/
enum class StateID {
	Idle = 0,
	Go_Left,
	Go_Right
};
struct State {
	unsigned int startFrame;
	unsigned int endFrame;
	bool isLoopable;
};
struct Animation {
	DWORD animationCounter;
	DWORD delayValue;
	unsigned int textureID;
	unsigned int currentFrame;
	StateID currentState;
	bool isFinished;
	std::unordered_map<StateID, State> stateDictionary;
};
