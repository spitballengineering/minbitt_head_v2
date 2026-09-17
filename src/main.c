#include <stdlib.h>
#include <assert.h> //TODO: do research to see if you should make your own


#include "raylib.h" // note: provides bool
#include "rlgl.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#ifdef EDITOR
#define GUI_MINBITT_EDITOR_IMPLEMENTATION
#include "gui_minbitt_editor.h"
#endif

#include "defaults.h"
#include "blendshapes.h"
#include "connection.h"
#include "controller.h"
#include "camera.h"
#include "front_screen.h"
#include "minbitt_face_animation.h"
#include "raymath.h"


// Button: SaveButton logic
void SaveButton(void) {
    // TODO: Implement control logic
    printf("pressed save\n");
}
// Button: LoadButton logic
void LoadButton(void) {
    // TODO: Implement control logic
    printf("pressed load\n");
}

 /*
 screen (hdmi)         shared
 camera (CSI/USB)      split
 Bluetooth controller  shared
 iPhone (Ethernet)     shared
 mic (audio in)        shared
 speaker (audio out)   shared
 led matrix (HUB75)    split
 fan                   ???
 portable battery      split
 */


typedef enum {
    MINBITT_FACE,
    DOOM,
    BADAPPLE,
} cartridge_type;

// designed to draw to internal screen (via normal raylib draw functions)
// and to the front screen (wheather it be a HUB75, TFT LCD, or a full HDMI) via frontScreenBuf
typedef void (cartridge_t)(blendshapes_t *blendshapes, float dt, controller_input *controller_input,
                           const connection_t *connection, Image *frontScreenBuf); //TODO: find better home

connection_t parse_args(int argc, char **argv) {
    //TODO:
    // minbitt_hud -m test_recording.txt
    // minbitt_hud 192.160.0.1 49983
    if (argc == 3) {
        return init_mock_connection(argv[2]);
    } else {
        return init_phone_connection();
    }
}


int main(int argc, char **argv) {
    // Parsing arguments
    //--------------------------------------------------------------------------------------
    const connection_t connection = parse_args(argc, argv);


    // Initialization
    //--------------------------------------------------------------------------------------
#ifdef EDITOR
    InitWindow(EDITOR_WIDTH, EDITOR_HEIGHT, "minbox");
    SetWindowMonitor(3); // DEBUG

    GuiMinbittEditorState gui = InitGuiMinbittEditor();
#else
    InitWindow(INSIDE_SCREEN_WIDTH, INSIDE_SCREEN_HEIGHT, "minbox");
    ToggleFullscreen();
    // SetExitKey(0); //TODO:
#endif


    Image cameraBuff = GenImageColor(CAM_WIDTH, CAM_HEIGHT, BLACK);
    Image frontScreenBuf = GenImageColor(FRONT_SCREEN_WIDTH, FRONT_SCREEN_HEIGHT, BLACK);
    Texture frontScreenTexture = LoadTextureFromImage(frontScreenBuf);
    assert(frontScreenBuf.format == frontScreenTexture.format &&
        "frontScreenBuf and frontScreenTexture formats do not match, they must match to pass data between them");

    // console variables
    cartridge_type loaded_cartridge = MINBITT_FACE;
    cartridge_t *cartridge = minbitt_face_cartridge;
    bool showFps = true;
    bool showBat = true;
    float dt = 0;
    blendshapes_t blendshapes = {0};
    SetTargetFPS(FPS);
    //--------------------------------------------------------------------------------------

    TRACELOG(LOG_ERROR, "starting minbox"); //TODO:
    // TraceLog(LOG_ERROR, "starting minbox");

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        get_blendshapes(connection, &blendshapes); // TODO: handel err cases
        controller_input controller_input = get_controller_input();
        dt = GetFrameTime();


        // -- load cartaridge --
        //TODO: first unload currenct cartridge
        switch (loaded_cartridge) {
            //TODO: maybe use function ptr?
            case MINBITT_FACE:
                cartridge = minbitt_face_cartridge;
                break;
            case DOOM:
                // doom(&blendshapes, dt);
                break;
            case BADAPPLE:
                // badapple(&blendshapes, dt);
                break;
            default:
                DrawText("Error: not valid cartridge", INSIDE_SCREEN_WIDTH / 2, INSIDE_SCREEN_HEIGHT / 2, 20, RED);
                break;
        }


        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
#ifdef EDITOR
            rlPushMatrix();
            rlTranslatef(gui.insideScreenRec.x, gui.insideScreenRec.y, 0);
#endif
            DrawText("MinboX console/OS?", 190, 200, 20, LIGHTGRAY);

            //TODO: display cam feed (maybe make it toggleable by the cartaridge for perf?)
            getCamreaFrame(&cameraBuff);

            // -- running catarage --
            //TODO: maybe seprate update and animat for face cartridge
            cartridge(&blendshapes, dt, &controller_input, &connection, &frontScreenBuf);

            //TODO: may need to be a Texture instead of Image
            draw_to_front_screen(&frontScreenBuf);
            //TODO: all draw cordnate frames debug lines when toggling bezier debug mode

            // -- menu --
            //TODO:

            // -- UI --
            if (showFps) DrawFPS(10, 10);
            if (showBat) DrawRectangle(15, INSIDE_SCREEN_HEIGHT - 40, 100, 20, PINK);


#ifdef EDITOR
            rlPopMatrix(); // undoes shift
            // -- editor gui --
            // Note this is before GuiMinbittEditor cuz that will set state.BlendEye... if user moves slider
            gui.BlendEyeLOpenSliderValue = (float)blendshapes.ARkit.eyeBlink_L;

            GuiMinbittEditor(&gui);

            // GuiSetStyle(DROPDOWNBOX, TEXT_PADDING, 4);
            // GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

            // front display preview
            UpdateTexture(frontScreenTexture, frontScreenBuf.data); // we can do this cuz of the assert at the top
            DrawTextureEx(frontScreenTexture, (Vector2){gui.frontScreenRec.x, gui.frontScreenRec.y}, 0, 7, WHITE);

            // other gui elements
            DrawRectangleLinesEx(gui.insideScreenRec, 2, GRAY);

            DrawRectangleLinesEx(gui.eyexyRec, 2, GRAY);
            DrawLineV((Vector2){gui.eyexyRec.x+gui.eyexyRec.width/2, gui.eyexyRec.y},
                (Vector2){gui.eyexyRec.x+gui.eyexyRec.width/2, gui.eyexyRec.y+gui.eyexyRec.height}, GRAY);
            DrawLineV((Vector2){gui.eyexyRec.x, gui.eyexyRec.y+gui.eyexyRec.height/2},
                (Vector2){gui.eyexyRec.x+gui.eyexyRec.width, gui.eyexyRec.y+gui.eyexyRec.height/2}, GRAY);

            //TODO: properly tune
            Vector2 eyeVec = {Clamp(blendshapes.left_eye.x*4, -10, 10),
                Clamp(blendshapes.left_eye.y, -5, 5)};
            eyeVec = Vector2Add(eyeVec, (Vector2){gui.eyexyRec.x + gui.eyexyRec.width/2, gui.eyexyRec.y+gui.eyexyRec.height/2});
            DrawCircleV(eyeVec, 7, PINK);
            DrawCircleV(eyeVec, 5, RED);

            // Vector2 pos = GetMousePosition();
            // char buff[256];
            // snprintf(buff, 256,"%3.0f, %3.0f", pos.x, pos.y);
            // DrawText(buff, 10, EDITOR_HEIGHT-80, 80, RED);

#endif
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadImage(frontScreenBuf);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
