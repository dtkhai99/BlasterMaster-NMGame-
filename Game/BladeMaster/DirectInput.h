#pragma once
#include<dinput.h>

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

class DirectInput
{
public:
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	void InitKeyboard(HWND hWnd);
	static DirectInput* GetInstance();
private:
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	static DirectInput* __instance;
};

