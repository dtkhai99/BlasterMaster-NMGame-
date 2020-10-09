#pragma once
#include "../Core/SystemBase.h"
#include <dinput.h>
class InputSystem :
    public SystemBase
{
public:
	virtual void KeyState(BYTE * states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

