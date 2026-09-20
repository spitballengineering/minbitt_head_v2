//
// Created by Spitball Engineering on 9/20/26.
//

#ifndef MINBITT_HEAD_V2_EDITOR_H
#define MINBITT_HEAD_V2_EDITOR_H

#define GUI_PROPERTY_LIST_IMPLEMENTATION
#include "external/dm_property_list.h"


struct {
    GuiDMProperty left_eye;
    GuiDMProperty right_eye;
    GuiDMProperty eye_tune_x;
    GuiDMProperty eye_tune_y;
    GuiDMProperty X3_thresh;
    GuiDMProperty eye_wide_thresh;
    GuiDMProperty eye_wide_upper_thresh;
    GuiDMProperty min_eye_wide;
    GuiDMProperty max_eye_wide;
    GuiDMProperty left_brow;
    GuiDMProperty right_brow;
    GuiDMProperty brow_tune;
    GuiDMProperty brow_down;
    GuiDMProperty brow_inner;
    GuiDMProperty mouth;
    GuiDMProperty mouth_horizontal;
    GuiDMProperty mouth_close;
    GuiDMProperty mouth_xy;
    GuiDMProperty talk_thresh;
    GuiDMProperty p0;
    GuiDMProperty p1;
    GuiDMProperty p2;
    GuiDMProperty left_blush;
    GuiDMProperty right_blush;
} typedef tuneProps;

typedef struct {
    int focus;
    int scroll;
    union {
        tuneProps props;
        GuiDMProperty arr[sizeof(tuneProps)/sizeof(GuiDMProperty)];
    };
} GuiTuneProps; //TODO: better name

struct {
    GuiDMProperty browDown_L;
    GuiDMProperty browDown_R;
    GuiDMProperty browInnerUp;
    GuiDMProperty browOuterUp_L;
    GuiDMProperty browOuterUp_R;
    GuiDMProperty cheekPuff;
    GuiDMProperty cheekSquint_L;
    GuiDMProperty cheekSquint_R;
    GuiDMProperty eyeBlink_L;
    GuiDMProperty eyeBlink_R;
    GuiDMProperty eyeLookDown_L;
    GuiDMProperty eyeLookDown_R;
    GuiDMProperty eyeLookIn_L;
    GuiDMProperty eyeLookIn_R;
    GuiDMProperty eyeLookOut_L;
    GuiDMProperty eyeLookOut_R;
    GuiDMProperty eyeLookUp_L;
    GuiDMProperty eyeLookUp_R;
    GuiDMProperty eyeSquint_L;
    GuiDMProperty eyeSquint_R;
    GuiDMProperty eyeWide_L;
    GuiDMProperty eyeWide_R;
    GuiDMProperty jawForward;
    GuiDMProperty jawLeft;
    GuiDMProperty jawOpen;
    GuiDMProperty jawRight;
    GuiDMProperty mouthClose;
    GuiDMProperty mouthDimple_L;
    GuiDMProperty mouthDimple_R;
    GuiDMProperty mouthFrown_L;
    GuiDMProperty mouthFrown_R;
    GuiDMProperty mouthFunnel;
    GuiDMProperty mouthLeft;
    GuiDMProperty mouthLowerDown_L;
    GuiDMProperty mouthLowerDown_R;
    GuiDMProperty mouthPress_L;
    GuiDMProperty mouthPress_R;
    GuiDMProperty mouthPucker;
    GuiDMProperty mouthRight;
    GuiDMProperty mouthRollLower;
    GuiDMProperty mouthRollUpper;
    GuiDMProperty mouthShrugLower;
    GuiDMProperty mouthShrugUpper;
    GuiDMProperty mouthSmile_L;
    GuiDMProperty mouthSmile_R;
    GuiDMProperty mouthStretch_L;
    GuiDMProperty mouthStretch_R;
    GuiDMProperty mouthUpperUp_L;
    GuiDMProperty mouthUpperUp_R;
    GuiDMProperty noseSneer_L;
    GuiDMProperty noseSneer_R;
    GuiDMProperty tongueOut;
}typedef blendshapesProps;

typedef struct {
    int focus;
    int scroll;
    union {
        blendshapesProps props;
        GuiDMProperty arr[sizeof(blendshapesProps)/sizeof(GuiDMProperty)];
    };
} GuiBlendshapesProps; //TODO: better name


GuiTuneProps GuiMinbittEditorTuneProp(void) {
    tuneProps r = {
        .left_eye = PVEC2("left eye", 0, 0, 0), //TODO: do all tool tips
        .right_eye = PVEC2("right eye", 0, 0, 0),
        .eye_tune_x = PSLIDER("eye tune x", 0, 0, 0, 100, "scaler for how much eyeball x is affected"),
        .eye_tune_y = PSLIDER("eye  tune y", 0, 0, 0, 100),
        .X3_thresh = PSLIDER("X3 thresh", 0, 0, 0, 100),
        .eye_wide_thresh = PSLIDER("eye wide thresh", 0, 0, 0, 100),
        .eye_wide_upper_thresh = PSLIDER("eye wide upper thresh", 0, 0, 0, 100),
        .min_eye_wide = PSLIDER("min eye wide", 0, 0, 0, 100),
        .max_eye_wide = PSLIDER("max eye wide", 0, 0, 0, 100),

        .left_brow = PVEC2("left brow", 0, 0, 0),
        .right_brow = PVEC2("right brow", 0, 0, 0),
        .brow_tune = PSLIDER("brow tune", 0, 0, 0, 100),
        .brow_down = PSLIDER("brow down", 0, 0, 0, 100),
        .brow_inner = PSLIDER("brow inner", 0, 0, 0, 100),

        .mouth = PVEC2("mouth", 0, 0, 0),
        .mouth_horizontal = PSLIDER("mouth horizontal", 0, 0, 0, 100),
        .mouth_close = PSLIDER("mouth close", 0, 0, 0, 100),
        .mouth_xy = PSLIDER("mouth xy", 0, 0, 0, 100),
        .talk_thresh = PSLIDER("talk thresh", 0, 0, 0, 100),
        .p0 = PVEC2("p0", 0, 0, 0),
        .p1 = PVEC2("p1", 0, 0, 0),
        .p2 = PVEC2("p2", 0, 0, 0),
        .left_blush = PVEC2("left blush", 0, 0, 0),
        .right_blush = PVEC2("right blush", 0, 0, 0),
    };
    return (GuiTuneProps){0,0, r};
}

GuiBlendshapesProps GuiMinbittEditorBlendshapesProp(void) {
    blendshapesProps r={//TODO: better name
        .browDown_L = PSLIDER("browDown_L", 0, 0, 0, 100),
        PSLIDER("browDown_R", 0, 0, 0, 100),
        PSLIDER("browInnerUp", 0, 0, 0, 100),
        PSLIDER("browOuterUp_L", 0, 0, 0, 100),
        PSLIDER("browOuterUp_R", 0, 0, 0, 100),
        PSLIDER("cheekPuff", 0, 0, 0, 100),
        PSLIDER("cheekSquint_L", 0, 0, 0, 100),
        PSLIDER("cheekSquint_R", 0, 0, 0, 100),
        PSLIDER("eyeBlink_L", 0, 0, 0, 100),
        PSLIDER("eyeBlink_R", 0, 0, 0, 100),
        PSLIDER("eyeLookDown_L", 0, 0, 0, 100),
        PSLIDER("eyeLookDown_R", 0, 0, 0, 100),
        PSLIDER("eyeLookIn_L", 0, 0, 0, 100),
        PSLIDER("eyeLookIn_R", 0, 0, 0, 100),
        PSLIDER("eyeLookOut_L", 0, 0, 0, 100),
        PSLIDER("eyeLookOut_R", 0, 0, 0, 100),
        PSLIDER("eyeLookUp_L", 0, 0, 0, 100),
        PSLIDER("eyeLookUp_R", 0, 0, 0, 100),
        PSLIDER("eyeSquint_L", 0, 0, 0, 100),
        PSLIDER("eyeSquint_R", 0, 0, 0, 100),
        PSLIDER("eyeWide_L", 0, 0, 0, 100),
        PSLIDER("eyeWide_R", 0, 0, 0, 100),
        PSLIDER("jawForward", 0, 0, 0, 100),
        PSLIDER("jawLeft", 0, 0, 0, 100),
        PSLIDER("jawOpen", 0, 0, 0, 100),
        PSLIDER("jawRight", 0, 0, 0, 100),
        PSLIDER("mouthClose", 0, 0, 0, 100),
        PSLIDER("mouthDimple_L", 0, 0, 0, 100),
        PSLIDER("mouthDimple_R", 0, 0, 0, 100),
        PSLIDER("mouthFrown_L", 0, 0, 0, 100),
        PSLIDER("mouthFrown_R", 0, 0, 0, 100),
        PSLIDER("mouthFunnel", 0, 0, 0, 100),
        PSLIDER("mouthLeft", 0, 0, 0, 100),
        PSLIDER("mouthLowerDown_L", 0, 0, 0, 100),
        PSLIDER("mouthLowerDown_R", 0, 0, 0, 100),
        PSLIDER("mouthPress_L", 0, 0, 0, 100),
        PSLIDER("mouthPress_R", 0, 0, 0, 100),
        PSLIDER("mouthPucker", 0, 0, 0, 100),
        PSLIDER("mouthRight", 0, 0, 0, 100),
        PSLIDER("mouthRollLower", 0, 0, 0, 100),
        PSLIDER("mouthRollUpper", 0, 0, 0, 100),
        PSLIDER("mouthShrugLower", 0, 0, 0, 100),
        PSLIDER("mouthShrugUpper", 0, 0, 0, 100),
        PSLIDER("mouthSmile_L", 0, 0, 0, 100),
        PSLIDER("mouthSmile_R", 0, 0, 0, 100),
        PSLIDER("mouthStretch_L", 0, 0, 0, 100),
        PSLIDER("mouthStretch_R", 0, 0, 0, 100),
        PSLIDER("mouthUpperUp_L", 0, 0, 0, 100),
        PSLIDER("mouthUpperUp_R", 0, 0, 0, 100),
        PSLIDER("noseSneer_L", 0, 0, 0, 100),
        PSLIDER("noseSneer_R", 0, 0, 0, 100),
        PSLIDER("tongueOut", 0, 0, 0, 100),
    };
    return (GuiBlendshapesProps){0,0,r};
}

#endif //MINBITT_HEAD_V2_EDITOR_H
