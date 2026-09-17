/*******************************************************************************************
*
*   MinbittEditor v1.0.0 - simple tool to tune face tracking data
*
*   MODULE USAGE:
*       #define GUI_MINBITT_EDITOR_IMPLEMENTATION
*       #include "gui_minbitt_editor.h"
*
*       INIT: GuiMinbittEditorState state = InitGuiMinbittEditor();
*       DRAW: GuiMinbittEditor(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 Spitball Engineering. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_MINBITT_EDITOR_H
#define GUI_MINBITT_EDITOR_H

typedef struct {
    // Define anchors
    Vector2 tuneAnchor;            // ANCHOR ID:1
    Vector2 blendshapesAnchor;            // ANCHOR ID:2
    Vector2 loadRecordingAnchor;            // ANCHOR ID:3
    Vector2 backgroundAnchor;            // ANCHOR ID:4
    Vector2 screenAnchor;            // ANCHOR ID:5
    Vector2 loadSaveAnchor;            // ANCHOR ID:6
    
    // Define controls variables
    float BlendEyeROpenSliderValue;            // Slider: BlendEyeROpenSlider
    float BlendEyeLOpenSliderValue;            // Slider: BlendEyeLOpenSlider
    float Slider012Value;            // Slider: Slider012
    float Slider013Value;            // Slider: Slider013
    float Slider014Value;            // Slider: Slider014
    float Slider015Value;            // Slider: Slider015
    float Slider016Value;            // Slider: Slider016
    float Slider017Value;            // Slider: Slider017
    float EyeXSliderValue;            // Slider: EyeXSlider
    float EyeYSliderValue;            // Slider: EyeYSlider
    float MouthSliderValue;            // Slider: MouthSlider
    float BrowSliderValue;            // Slider: BrowSlider
    bool BackgroundDropdownBoxEditMode;
    int BackgroundDropdownBoxActive;            // DropdownBox: BackgroundDropdownBox
    bool LoadRecordingDropdownBoxEditMode;
    int LoadRecordingDropdownBoxActive;            // DropdownBox: LoadRecordingDropdownBox
    bool BezierCheckBoxExChecked;            // CheckBoxEx: BezierCheckBoxEx
    int GifListViewScrollIndex;
    int GifListViewActive;            // ListView: GifListView

    // Define rectangles
    // Init controls rectangles
    Rectangle StatusBarRec;
    Rectangle BlendshapeGroupBoxRec;
    Rectangle BlendEyeROpenSliderRec;
    Rectangle BlendEyeLOpenSliderRec;
    Rectangle Slider012Rec;
    Rectangle Slider013Rec;
    Rectangle Slider014Rec;
    Rectangle Slider015Rec;
    Rectangle Slider016Rec;
    Rectangle Slider017Rec;
    Rectangle EyeXSliderRec;
    Rectangle EyeYSliderRec;
    Rectangle MouthSliderRec;
    Rectangle BrowSliderRec;
    Rectangle LoadRecordingLabelRec;
    Rectangle SaveButtonRec;
    Rectangle BackgroundDropdownBoxRec;
    Rectangle BackgroundLabelRec;
    Rectangle LoadRecordingDropdownBoxRec;
    Rectangle BezierCheckBoxExRec;
    Rectangle GifListViewRec;
    Rectangle FrontScreenCordLabelRec;
    Rectangle LoadButtonRec;
    Rectangle BlendEyeXLabelRec;
    Rectangle BlendEyeYLabelRec;
    Rectangle BlendEyeXValLabelRec;
    Rectangle BlendEyeYValLabelRec;
    Rectangle insideScreenRec;
    Rectangle frontScreenRec;
    Rectangle controllerRec;
    Rectangle eyexyRec;


    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiMinbittEditorState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiMinbittEditorState InitGuiMinbittEditor(void);
void GuiMinbittEditor(GuiMinbittEditorState *state);
extern void SaveButton();                // Button: SaveButton logic
extern void LoadButton();                // Button: LoadButton logic

#ifdef __cplusplus
}
#endif

#endif // GUI_MINBITT_EDITOR_H

/***********************************************************************************
*
*   GUI_MINBITT_EDITOR IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_MINBITT_EDITOR_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
    // Const text
    const char *BlendshapeGroupBoxText = "blendshapes";    // GROUPBOX: BlendshapeGroupBox
    char BlendEyeROpenSliderText[] = "eye Right open";    // SLIDER: BlendEyeROpenSlider
    char BlendEyeLOpenSliderText[] = "eye Left Open";    // SLIDER: BlendEyeLOpenSlider
    char Slider012Text[] = "todo";    // SLIDER: Slider012
    char Slider013Text[] = "todo";    // SLIDER: Slider013
    char Slider014Text[] = "todo";    // SLIDER: Slider014
    char Slider015Text[] = "todo";    // SLIDER: Slider015
    char Slider016Text[] = "todo";    // SLIDER: Slider016
    char Slider017Text[] = "todo";    // SLIDER: Slider017
    char EyeXSliderText[] = "eye tune x -00.00";    // SLIDER: EyeXSlider
    char EyeYSliderText[] = "eye tune y -00.00";    // SLIDER: EyeYSlider
    char MouthSliderText[] = "mouth tune -00.00";    // SLIDER: MouthSlider
    char BrowSliderText[] = "brow tune -00.00";    // SLIDER: BrowSlider
    const char *LoadRecordingLabelText = "load recording";    // LABEL: LoadRecordingLabel
    const char *SaveButtonText = "#002#save config";    // BUTTON: SaveButton
    const char *BackgroundDropdownBoxText = "ONE;TWO;THREE";    // DROPDOWNBOX: BackgroundDropdownBox
    const char *BackgroundLabelText = "backgrounds:";    // LABEL: BackgroundLabel
    const char *LoadRecordingDropdownBoxText = "ONE;TWO;THREE";    // DROPDOWNBOX: LoadRecordingDropdownBox
    const char *BezierCheckBoxExText = "toggle bezier curve debug lines";    // CHECKBOXEX: BezierCheckBoxEx
    const char *GifListViewText = "ONE;TWO;THREE; four; five; six; seven; 8;9;10;etc...";    // LISTVIEW: GifListView
    const char *FrontScreenCordLabelText = "(20, 40)";    // LABEL: FrontScreenCordLabel
    const char *LoadButtonText = "#005#load config";    // BUTTON: LoadButton
    const char *BlendEyeXLabelText = "eyeball x";    // LABEL: BlendEyeXLabel
    const char *BlendEyeYLabelText = "eyeball y";    // LABEL: BlendEyeYLabel
    char BlendEyeXValLabelText[] = "-00.00";    // LABEL: BlendEyeXValLabel
    char BlendEyeYValLabelText[] = "-00.00";    // LABEL: BlendEyeYValLabel
    const char *insideScreenText = "inside screen";    // DUMMYREC: insideScreen
    const char *frontScreenText = "front screen";    // DUMMYREC: frontScreen
    const char *controllerText = "controller";    // DUMMYREC: controller
    const char *eyexyText = "eyeball xy";    // DUMMYREC: eyexy
    

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiMinbittEditorState InitGuiMinbittEditor(void)
{
    GuiMinbittEditorState state = { 0 };

    // Init anchors
    state.tuneAnchor = (Vector2){ 30, 50 };            // ANCHOR ID:1
    state.blendshapesAnchor = (Vector2){ 1200, 40 };            // ANCHOR ID:2
    state.loadRecordingAnchor = (Vector2){ 20, 10 };            // ANCHOR ID:3
    state.backgroundAnchor = (Vector2){ 575, 10 };            // ANCHOR ID:4
    state.screenAnchor = (Vector2){ 385, 50 };            // ANCHOR ID:5
    state.loadSaveAnchor = (Vector2){ 1400, 5 };            // ANCHOR ID:6
    
    // Initilize controls variables
    state.BlendEyeROpenSliderValue = 0.0f;            // Slider: BlendEyeROpenSlider
    state.BlendEyeLOpenSliderValue = 0.0f;            // Slider: BlendEyeLOpenSlider
    state.Slider012Value = 0.0f;            // Slider: Slider012
    state.Slider013Value = 0.0f;            // Slider: Slider013
    state.Slider014Value = 0.0f;            // Slider: Slider014
    state.Slider015Value = 0.0f;            // Slider: Slider015
    state.Slider016Value = 0.0f;            // Slider: Slider016
    state.Slider017Value = 0.0f;            // Slider: Slider017
    state.EyeXSliderValue = 0.0f;            // Slider: EyeXSlider
    state.EyeYSliderValue = 0.0f;            // Slider: EyeYSlider
    state.MouthSliderValue = 0.0f;            // Slider: MouthSlider
    state.BrowSliderValue = 0.0f;            // Slider: BrowSlider
    state.BackgroundDropdownBoxEditMode = false;
    state.BackgroundDropdownBoxActive = 0;            // DropdownBox: BackgroundDropdownBox
    state.LoadRecordingDropdownBoxEditMode = false;
    state.LoadRecordingDropdownBoxActive = 0;            // DropdownBox: LoadRecordingDropdownBox
    state.BezierCheckBoxExChecked = false;            // CheckBoxEx: BezierCheckBoxEx
    state.GifListViewScrollIndex = 0;
    state.GifListViewActive = 0;            // ListView: GifListView

    // Init controls rectangles
    state.StatusBarRec = (Rectangle){ 0, 0, 1600, 40 };// StatusBar: StatusBar
    state.BlendshapeGroupBoxRec = (Rectangle){ state.blendshapesAnchor.x + -5, state.blendshapesAnchor.y + 10, 395, 830 };// GroupBox: BlendshapeGroupBox
    state.BlendEyeROpenSliderRec = (Rectangle){ state.blendshapesAnchor.x + 115, state.blendshapesAnchor.y + 125, 240, 15 };// Slider: BlendEyeROpenSlider
    state.BlendEyeLOpenSliderRec = (Rectangle){ state.blendshapesAnchor.x + 115, state.blendshapesAnchor.y + 155, 240, 15 };// Slider: BlendEyeLOpenSlider
    state.Slider012Rec = (Rectangle){ state.blendshapesAnchor.x + 115, state.blendshapesAnchor.y + 185, 240, 15 };// Slider: Slider012
    state.Slider013Rec = (Rectangle){ state.blendshapesAnchor.x + 115, state.blendshapesAnchor.y + 215, 240, 15 };// Slider: Slider013
    state.Slider014Rec = (Rectangle){ state.blendshapesAnchor.x + 115, state.blendshapesAnchor.y + 245, 240, 15 };// Slider: Slider014
    state.Slider015Rec = (Rectangle){ state.blendshapesAnchor.x + 115, state.blendshapesAnchor.y + 275, 240, 17 };// Slider: Slider015
    state.Slider016Rec = (Rectangle){ state.blendshapesAnchor.x + 115, state.blendshapesAnchor.y + 305, 240, 15 };// Slider: Slider016
    state.Slider017Rec = (Rectangle){ state.blendshapesAnchor.x + 115, state.blendshapesAnchor.y + 335, 240, 15 };// Slider: Slider017
    state.EyeXSliderRec = (Rectangle){ state.tuneAnchor.x + 75, state.tuneAnchor.y + 0, 270, 15 };// Slider: EyeXSlider
    state.EyeYSliderRec = (Rectangle){ state.tuneAnchor.x + 75, state.tuneAnchor.y + 30, 270, 16 };// Slider: EyeYSlider
    state.MouthSliderRec = (Rectangle){ state.tuneAnchor.x + 75, state.tuneAnchor.y + 60, 270, 15 };// Slider: MouthSlider
    state.BrowSliderRec = (Rectangle){ state.tuneAnchor.x + 75, state.tuneAnchor.y + 90, 270, 15 };// Slider: BrowSlider
    state.LoadRecordingLabelRec = (Rectangle){ state.loadRecordingAnchor.x + 0, state.loadRecordingAnchor.y + 0, 80, 20 };// Label: LoadRecordingLabel
    state.SaveButtonRec = (Rectangle){ state.loadSaveAnchor.x + 100, state.loadSaveAnchor.y + 0, 95, 30 };// Button: SaveButton
    state.BackgroundDropdownBoxRec = (Rectangle){ state.backgroundAnchor.x + 80, state.backgroundAnchor.y + 0, 185, 20 };// DropdownBox: BackgroundDropdownBox
    state.BackgroundLabelRec = (Rectangle){ state.backgroundAnchor.x + 0, state.backgroundAnchor.y + 0, 80, 20 };// Label: BackgroundLabel
    state.LoadRecordingDropdownBoxRec = (Rectangle){ state.loadRecordingAnchor.x + 80, state.loadRecordingAnchor.y + 0, 115, 20 };// DropdownBox: LoadRecordingDropdownBox
    state.BezierCheckBoxExRec = (Rectangle){ 60, 575, 24, 24 };// CheckBoxEx: BezierCheckBoxEx
    state.GifListViewRec = (Rectangle){ 45, 615, 285, 265 };// ListView: GifListView
    state.FrontScreenCordLabelRec = (Rectangle){ state.screenAnchor.x + 0, state.screenAnchor.y + 835, 50, 15 };// Label: FrontScreenCordLabel
    state.LoadButtonRec = (Rectangle){ state.loadSaveAnchor.x + 0, state.loadSaveAnchor.y + 0, 95, 30 };// Button: LoadButton
    state.BlendEyeXLabelRec = (Rectangle){ state.blendshapesAnchor.x + 60, state.blendshapesAnchor.y + 45, 55, 15 };// Label: BlendEyeXLabel
    state.BlendEyeYLabelRec = (Rectangle){ state.blendshapesAnchor.x + 60, state.blendshapesAnchor.y + 75, 50, 15 };// Label: BlendEyeYLabel
    state.BlendEyeXValLabelRec = (Rectangle){ state.blendshapesAnchor.x + 295, state.blendshapesAnchor.y + 45, 35, 20 };// Label: BlendEyeXValLabel
    state.BlendEyeYValLabelRec = (Rectangle){ state.blendshapesAnchor.x + 295, state.blendshapesAnchor.y + 75, 35, 20 };// Label: BlendEyeYValLabel
    state.insideScreenRec = (Rectangle){ state.screenAnchor.x + 0, state.screenAnchor.y + 0, 800, 600 };// DummyRec: insideScreen
    state.frontScreenRec = (Rectangle){ state.screenAnchor.x + 0, state.screenAnchor.y + 610, 450, 220 };// DummyRec: frontScreen
    state.controllerRec = (Rectangle){ state.screenAnchor.x + 465, state.screenAnchor.y + 610, 335, 220 };// DummyRec: controller
    state.eyexyRec = (Rectangle){ state.blendshapesAnchor.x + 130, state.blendshapesAnchor.y + 25, 150, 75 };// DummyRec: eyexy

    // Custom variables initialization

    return state;
}
// Button: SaveButton logic
// Button: LoadButton logic


void GuiMinbittEditor(GuiMinbittEditorState *state)
{
    // Draw controls
    if (state->BackgroundDropdownBoxEditMode || state->LoadRecordingDropdownBoxEditMode) GuiLock();

    GuiStatusBar(state->StatusBarRec, NULL);
    GuiGroupBox(state->BlendshapeGroupBoxRec, BlendshapeGroupBoxText);
    GuiSlider(state->BlendEyeROpenSliderRec, BlendEyeROpenSliderText, NULL, &state->BlendEyeROpenSliderValue, 0, 100);
    GuiSlider(state->BlendEyeLOpenSliderRec, BlendEyeLOpenSliderText, NULL, &state->BlendEyeLOpenSliderValue, 0, 100);
    GuiSlider(state->Slider012Rec, Slider012Text, NULL, &state->Slider012Value, 0, 100);
    GuiSlider(state->Slider013Rec, Slider013Text, NULL, &state->Slider013Value, 0, 100);
    GuiSlider(state->Slider014Rec, Slider014Text, NULL, &state->Slider014Value, 0, 100);
    GuiSlider(state->Slider015Rec, Slider015Text, NULL, &state->Slider015Value, 0, 100);
    GuiSlider(state->Slider016Rec, Slider016Text, NULL, &state->Slider016Value, 0, 100);
    GuiSlider(state->Slider017Rec, Slider017Text, NULL, &state->Slider017Value, 0, 100);
    GuiSlider(state->EyeXSliderRec, EyeXSliderText, NULL, &state->EyeXSliderValue, 0, 100);
    GuiSlider(state->EyeYSliderRec, EyeYSliderText, NULL, &state->EyeYSliderValue, 0, 100);
    GuiSlider(state->MouthSliderRec, MouthSliderText, NULL, &state->MouthSliderValue, 0, 100);
    GuiSlider(state->BrowSliderRec, BrowSliderText, NULL, &state->BrowSliderValue, 0, 100);
    GuiLabel(state->LoadRecordingLabelRec, LoadRecordingLabelText);
    if (GuiButton(state->SaveButtonRec, SaveButtonText)) SaveButton(); 
    GuiLabel(state->BackgroundLabelRec, BackgroundLabelText);
    GuiCheckBox(state->BezierCheckBoxExRec, BezierCheckBoxExText, &state->BezierCheckBoxExChecked);
    GuiListView(state->GifListViewRec, GifListViewText, &state->GifListViewScrollIndex, &state->GifListViewActive);
    GuiLabel(state->FrontScreenCordLabelRec, FrontScreenCordLabelText);
    if (GuiButton(state->LoadButtonRec, LoadButtonText)) LoadButton(); 
    GuiLabel(state->BlendEyeXLabelRec, BlendEyeXLabelText);
    GuiLabel(state->BlendEyeYLabelRec, BlendEyeYLabelText);
    GuiLabel(state->BlendEyeXValLabelRec, BlendEyeXValLabelText);
    GuiLabel(state->BlendEyeYValLabelRec, BlendEyeYValLabelText);
    if (GuiDropdownBox(state->BackgroundDropdownBoxRec, BackgroundDropdownBoxText, &state->BackgroundDropdownBoxActive, state->BackgroundDropdownBoxEditMode)) state->BackgroundDropdownBoxEditMode = !state->BackgroundDropdownBoxEditMode;
    if (GuiDropdownBox(state->LoadRecordingDropdownBoxRec, LoadRecordingDropdownBoxText, &state->LoadRecordingDropdownBoxActive, state->LoadRecordingDropdownBoxEditMode)) state->LoadRecordingDropdownBoxEditMode = !state->LoadRecordingDropdownBoxEditMode;
    
    GuiUnlock();
}

#endif // GUI_MINBITT_EDITOR_IMPLEMENTATION
