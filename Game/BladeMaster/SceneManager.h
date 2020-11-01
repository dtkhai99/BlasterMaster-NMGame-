#pragma once
/*
	Approach 1:
	Our main goal is to create a scene manager with no limit to the number of elements and distinct elements it 
	can show and to provide an easy way to add new scenes. One way to ensure a working scene flow (allowing the 
	user to go back and forth between scenes) is to use a stack of scene.

	The top scene on the stack will be the currently active scene and going to a new scene means simply pushing 
	that scene on the stack, while going back means popping the top scene off the stack. Another thing to consider 
	is that sometimes multiple scenes must be visible

	For more information: https://bell0bytes.eu/scene-manager/

	Approach 2:
	Use Facade or Mediator design pattern
*/
class SceneManager
{
};

