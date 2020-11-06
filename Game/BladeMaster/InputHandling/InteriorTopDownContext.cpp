#include "InteriorTopDownContext.h"
#include "WeaponSelectCommand.h"
#include "GoLeftInteriorCommand.h"
#include "GoRightInteriorCommand.h"
#include "GoUpInteriorCommand.h"
#include "GoDownInteriorCommand.h"
#include "TossGrenadeCommand.h"
#include "ShootInteriorCommand.h"
#include<dinput.h>

InteriorTopDownContext::InteriorTopDownContext() {
    start_button = new WeaponSelectCommand();
    left = new GoLeftInteriorCommand();
    up = new GoUpInteriorCommand();
    right = new GoRightInteriorCommand();
    down = new GoDownInteriorCommand();
    a_button = new TossGrenadeCommand();
    b_button = new ShootInteriorCommand();
}

bool InteriorTopDownContext::Handle(MappedInput & mappedInput) {
    if(!isActive) return false;
    if(mappedInput.bufferedKeyEvent[DIK_RETURN]) {
        start_button->execute();
    } if(mappedInput.bufferedKeyEvent[DIK_Z]) {
        a_button->execute();
    } else if(mappedInput.bufferedKeyEvent[DIK_X]) {
        b_button->execute();
    }

    if(mappedInput.keyStates[DIK_UP] & 0x80) {
        up->execute();
    } else if(mappedInput.keyStates[DIK_LEFT] & 0x80) {
        left->execute();
    } else if(mappedInput.keyStates[DIK_RIGHT] & 0x80) {
        right->execute();
    } else if (mappedInput.keyStates[DIK_DOWN] & 0x80) {
        down->execute();
    }

    return true;
}
