#pragma once
#include "Core/Context.h"

class Command;
class ExteriorSideScrollingContext : public Context {
public:
  ExteriorSideScrollingContext();
  bool Handle(MappedInput &);

private:
  Command * up;
  Command * down;
  Command * left;
  Command * right;
  Command * a_button;
  Command * b_button;
  Command * start_button;
  Command * select_button;
};
