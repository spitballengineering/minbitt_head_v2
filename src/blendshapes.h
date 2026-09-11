//
// Created by Spitball Engineering on 9/11/26.
//

#ifndef MINBITT_HEAD_V2_BLENDSHAPES_H
#define MINBITT_HEAD_V2_BLENDSHAPES_H

typedef struct blendshapes {
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
    int trackingStatus; // TODO: seprate from 52 blendshapes?
} blendshapes;

#endif //MINBITT_HEAD_V2_BLENDSHAPES_H
