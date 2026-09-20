//
// Created by Spitball Engineering on 9/11/26.
//

#ifndef MINBITT_HEAD_V2_BLENDSHAPES_H
#define MINBITT_HEAD_V2_BLENDSHAPES_H

#include <stdio.h> //TODO: remove
#include "string.h" //TODO: remove
#include <stdlib.h>//TODO: remove

#define NUM_BLENDSHAPES 52

struct ARkit {
    int browDown_L;
    int browDown_R;
    int browInnerUp;
    int browOuterUp_L;
    int browOuterUp_R;
    int cheekPuff;
    int cheekSquint_L;
    int cheekSquint_R;
    int eyeBlink_L;
    int eyeBlink_R;
    int eyeLookDown_L;
    int eyeLookDown_R;
    int eyeLookIn_L;
    int eyeLookIn_R;
    int eyeLookOut_L;
    int eyeLookOut_R;
    int eyeLookUp_L;
    int eyeLookUp_R;
    int eyeSquint_L;
    int eyeSquint_R;
    int eyeWide_L;
    int eyeWide_R;
    int jawForward;
    int jawLeft;
    int jawOpen;
    int jawRight;
    int mouthClose;
    int mouthDimple_L;
    int mouthDimple_R;
    int mouthFrown_L;
    int mouthFrown_R;
    int mouthFunnel;
    int mouthLeft;
    int mouthLowerDown_L;
    int mouthLowerDown_R;
    int mouthPress_L;
    int mouthPress_R;
    int mouthPucker;
    int mouthRight;
    int mouthRollLower;
    int mouthRollUpper;
    int mouthShrugLower;
    int mouthShrugUpper;
    int mouthSmile_L;
    int mouthSmile_R;
    int mouthStretch_L;
    int mouthStretch_R;
    int mouthUpperUp_L;
    int mouthUpperUp_R;
    int noseSneer_L;
    int noseSneer_R;
    int tongueOut;
};

typedef struct blendshapes {
    struct ARkit ARkit;
    int trackingStatus;
    struct {
        float x;
        float y;
        float z;
        float ax;
        float ay;
        float az;
    } head;
    struct {
        float x;
        float y;
        float z;
    } right_eye;
    struct {
        float x;
        float y;
        float z;
    } left_eye;
} blendshapes_t;

static const char *iFacialmocap_field_arr[] = {
    "browDown_L", "browDown_R", "browInnerUp", "browOuterUp_L", "browOuterUp_R", "cheekPuff", "cheekSquint_L",
    "cheekSquint_R", "eyeBlink_L", "eyeBlink_R", "eyeLookDown_L", "eyeLookDown_R", "eyeLookIn_L", "eyeLookIn_R",
    "eyeLookOut_L", "eyeLookOut_R", "eyeLookUp_L", "eyeLookUp_R", "eyeSquint_L", "eyeSquint_R", "eyeWide_L",
    "eyeWide_R", "jawForward", "jawLeft", "jawOpen", "jawRight", "mouthClose", "mouthDimple_L", "mouthDimple_R",
    "mouthFrown_L", "mouthFrown_R", "mouthFunnel", "mouthLeft", "mouthLowerDown_L", "mouthLowerDown_R",
    "mouthPress_L", "mouthPress_R", "mouthPucker", "mouthRight", "mouthRollLower", "mouthRollUpper",
    "mouthShrugLower", "mouthShrugUpper", "mouthSmile_L", "mouthSmile_R", "mouthStretch_L", "mouthStretch_R",
    "mouthUpperUp_L", "mouthUpperUp_R", "noseSneer_L", "noseSneer_R", "tongueOut", "trackingStatus"
};

static inline void blendshapes_set_field(blendshapes_t *blendshapes, char *field, int val) {
    //TODO: optimize
    for (int i = 0; i < NUM_BLENDSHAPES + 1; ++i) {
        if (strcmp(field, iFacialmocap_field_arr[i]) == 0) {
            *((int *) &blendshapes->ARkit + i) = val; // kek
            return;
        }
    }
    if (strcmp(field, "hapihapi") == 0) return; // special case
    if (strcmp(field, "none") == 0) return;
    fprintf(stderr, "warning: %s field type not found\n", field);
    exit(1);
}

#endif //MINBITT_HEAD_V2_BLENDSHAPES_H
