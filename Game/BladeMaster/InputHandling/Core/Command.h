#pragma once
/*
  I use command pattern here

  More information:
  https://gameprogrammingpatterns.com/command.html

  Because we have situation like if we hold jump button longer, the character will jump higher and if we just press jump 
  button one, the character will jump lower. So I decided to leave a flag here in order to distinguish between hold and press.
  For another situations, like shooting. They don't need to distinguish between hold and press. So normally we don't check isHold flag
  If there are any design better, I will consider change it
*/
class Command {
public:
  virtual ~Command() {}
  virtual void execute() = 0;
public:
  bool isHold = false;
};
