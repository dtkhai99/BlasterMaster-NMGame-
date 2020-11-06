#pragma once
#include "MappedInput.h"
//This is third layer of Input Handling System
/*
  the third layer will implement your specific game's responses to the input it receives

  More information:
  https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/designing-a-robust-input-handling-system-for-games-r2975/

  Each context will be able to map input to Command.
  I will use Command Pattern here

  More information:
  https://gameprogrammingpatterns.com/command.html
*/
class Context {
public:
  virtual bool Handle(MappedInput &) = 0;

public:
  bool isActive; //We need to track which 
};
