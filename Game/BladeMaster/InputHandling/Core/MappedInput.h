#pragma once
#include <dinput.h>

struct MappedInput {
  BYTE  keyStates[256];

  //Assumed all key is up
  //True - key is down
  //False - key is up
  bool  bufferedKeyEvent[256];
};
