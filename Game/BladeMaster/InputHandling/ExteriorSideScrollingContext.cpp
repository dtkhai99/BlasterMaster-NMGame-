#include "ExteriorSideScrollingContext.h"
#include "JumpCommand.h"
#include "WeaponSelectCommand.h"
#include "SwitchModeCommand.h"
#include "ShootExteriorCommand.h"
#include "GoLeftExteriorCommand.h"
#include "GoRightExteriorCommand.h"
#include "AimUpCommand.h"
#include "LayDownCommand.h"
#include <dinput.h>

//ExteriorSideScrollingContext::ExteriorSideScrollingContext() {
//  up = new AimUpCommand();
//  start_button = new WeaponSelectCommand();
//  select_button = new SwitchModeCommand();
//  b_button = new ShootExteriorCommand();
//  left = new GoLeftExteriorCommand();
//  right = new GoRightExteriorCommand();
//  a_button = new JumpCommand();
//  down = new LayDownCommand();
//}

//bool ExteriorSideScrollingContext::Handle(MappedInput & mappedInput) {
//  if(mappedInput.bufferedKeyEvent[DIK_DOWN]) {
//    down->execute();
//  } else if(mappedInput.bufferedKeyEvent[DIK_LSHIFT]) {
//    select_button->execute();
//  } else if(mappedInput.bufferedKeyEvent[DIK_RETURN]) {
//    start_button->execute();
//  } else if(mappedInput.bufferedKeyEvent[DIK_UP]) {
//    up->execute();
//  } else if(mappedInput.bufferedKeyEvent[DIK_Z]) {
//    a_button->execute();
//  } else if(mappedInput.bufferedKeyEvent[DIK_X]) {
//    b_button->execute();
//  }
//
//  if(mappedInput.keyStates[DIK_UP] & 0x80) {
//    up->execute();
//    up->isHold = true;
//  } else if(mappedInput.keyStates[DIK_LEFT] & 0x80) {
//    left->execute();
//  } else if(mappedInput.keyStates[DIK_RIGHT] & 0x80) {
//    right->execute();  
//  } else if(mappedInput.keyStates[DIK_Z] & 0x80) {
//    a_button->execute();
//    a_button->isHold = true;
//  } 
//}
