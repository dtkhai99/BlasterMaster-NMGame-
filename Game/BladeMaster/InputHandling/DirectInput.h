#pragma once
#include<dinput.h>
#include "InputContext.h"

//This is first layer in Input Handling System
/*
	This class gathers raw input data from the hardware and packs all of available input into an object
	and then send to second layer

	More information:
	https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/designing-a-robust-input-handling-system-for-games-r2975/
*/

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

class DirectInput
{
public:
	//int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	void InitKeyboard(HWND hWnd);
	static DirectInput* GetInstance();
private:
	LPDIRECTINPUT8       di;		// The DirectInput object
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device

	InputContext * inputContext;
	//BYTE  keyStates[256];			// DirectInput keyboard state buffer
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	static DirectInput* __instance;
};
