//
// Created by Spitball Engineering on 9/11/26.
//

#ifndef MINBITT_HEAD_V2_CONTROLLER_H
#define MINBITT_HEAD_V2_CONTROLLER_H

#include "raylib.h" // needed for bool

typedef struct {
    bool dpad_up;
    bool dpad_down;
    bool dpad_left;
    bool dpad_right;
    bool btn_up;
    bool btn_down;
    bool btn_left;
    bool btn_right;
    bool l_trigger;
    bool r_trigger;
} controller_input;

controller_input get_controller_input();

#endif //MINBITT_HEAD_V2_CONTROLLER_H