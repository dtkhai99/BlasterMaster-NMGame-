#include "ExteriorSideScrollingContext.h"
#include "JumpCommand.h"
#include "WeaponSelectCommand.h"
#include "SwitchModeCommand.h"
#include "ShootCommand.h"
#include "GoLeftCommand.h"
#include "GoRightCommand.h"
#include <dinput.h>

ExteriorSideScrollingContext::ExteriorSideScrollingContext() {
  upPress = new JumpCommand();
  start_button = new WeaponSelectCommand();
  select_button = new SwitchModeCommand();
  b_button = new ShootCommand();
  left = new GoLeftCommand();
  right = new GoRightCommand();
}

bool ExteriorSideScrollingContext::Handle(MappedInput & mappedInput) {
  if(mappedInput.bufferedKeyEvent[DIK_DOWN]) {
    down->execute();
  } else if(mappedInput.bufferedKeyEvent[DIK_LSHIFT]) {
    select_button->execute();
  } else if(mappedInput.bufferedKeyEvent[DIK_RETURN]) {
    start_button->execute();
  } else if(mappedInput.bufferedKeyEvent[DIK_UP]) {
    upPress->execute();
  } else if(mappedInput.bufferedKeyEvent[DIK_Z]) {
    a_button_press->execute();
  } else if(mappedInput.bufferedKeyEvent[DIK_X]) {
    b_button->execute();
  }

  if(mappedInput.keyStates[DIK_UP] & 0x80) {
    upHold->execute();
  } else if(mappedInput.keyStates[DIK_LEFT] & 0x80) {
    left->execute();
  } else if(mappedInput.keyStates[DIK_RIGHT] & 0x80) {
    right->execute();  
  } else if(mappedInput.keyStates[DIK_Z] & 0x80) {
    a_button_hold->execute();
  } 
}
