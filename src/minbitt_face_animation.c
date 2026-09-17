#include "minbitt_face_animation.h"

#include "defaults.h"

void minbitt_face_cartridge_init() {
    //TODO: have this load a confic that was generated from the minbitt editor
}

void minbitt_face_cartridge(blendshapes* blendshapes, float dt, controller_input *controller_input, const connection_t* connection, Image *frontScreenBuf){
    // custom gifs
    if (controller_input->l_trigger) {
        unsigned int *key_combo = (unsigned int *) controller_input;
        switch (*key_combo) {
            case 0b000: DrawRectangle(INSIDE_SCREEN_WIDTH / 2, INSIDE_SCREEN_HEIGHT / 2, 80, 80, RED);
                break;
            case 0b001: DrawRectangle(INSIDE_SCREEN_WIDTH / 2, INSIDE_SCREEN_HEIGHT / 2, 80, 80, BLUE);
                break;
            case 0b111: DrawRectangle(INSIDE_SCREEN_WIDTH / 2, INSIDE_SCREEN_HEIGHT / 2, 80, 80, GREEN);
                break;
            default: break; //TODO: show black
        }
    }

    if (!blendshapes->trackingStatus) DrawRectangleLinesEx((Rectangle){0,0, (float)INSIDE_SCREEN_WIDTH, (float)INSIDE_SCREEN_HEIGHT}, 10, RED);
}
