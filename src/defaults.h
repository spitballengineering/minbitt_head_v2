//
// Created by Spitball Engineering on 9/11/26.
//

#ifndef MINBITT_HEAD_V2_DEFAULTS_H
#define MINBITT_HEAD_V2_DEFAULTS_H

#ifdef EDITOR
// EDITOR_WIDTH and HEIGHT should only ever be used if we are in EDITOR mode
#define EDITOR_WIDTH 1600
#define EDITOR_HEIGHT 900
#endif

#define INSIDE_SCREEN_WIDTH 800
#define INSIDE_SCREEN_HEIGHT 600
#define FRONT_SCREEN_WIDTH 64
#define FRONT_SCREEN_HEIGHT 32
#define CAM_WIDTH 100
#define CAM_HEIGHT 100
#define FPS 60

// TODO: ask for minbit blue
#define MINBITT_BLUE CLITERAL(Color){0x5f, 0xcd, 0xe4, 0xff} //0x5fcde4

#endif //MINBITT_HEAD_V2_DEFAULTS_H
