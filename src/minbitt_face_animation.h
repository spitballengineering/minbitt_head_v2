//
// Created by Spitball Engineering on 9/11/26.
//

#ifndef MINBITT_HEAD_V2_MINBITT_FACE_ANIMATION_H
#define MINBITT_HEAD_V2_MINBITT_FACE_ANIMATION_H

#include "raylib.h"

#include "blendshapes.h"
#include "controller.h"
#include "connection.h"

void minbitt_face_cartridge(blendshapes* blendshapes, float dt, controller_input *controller_input, const connection_t* connection, Image *frontScreenBuf);

#endif //MINBITT_HEAD_V2_MINBITT_FACE_ANIMATION_H