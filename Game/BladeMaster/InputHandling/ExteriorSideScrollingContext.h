#pragma once
#include "Context.h"

class Command;
class ExteriorSideScrollingContext : public Context {
public:
  ExteriorSideScrollingContext();
  bool Handle(MappedInput &);

private:
  Command * upHold;
  Command * upPress;
  Command * down;
  Command * left;
  Command * right;
  Command * a_button_hold;
  Command * a_button_press;
  Command * b_button;
  Command * start_button;
  Command * select_button;
};
