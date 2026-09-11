#include <stdlib.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


#include "blendshapes.h"
#include "connection.h"
#include "controller.h"
#include "camera.h"
#include "front_screen.h"
#include "minbitt_face_animation.h"

// TODO: ask for minbit blue
#define MINBITT_BLUE CLITERAL(Color){0x5f, 0xcd, 0xe4, 0xff} //0x5fcde4

/**
- screen (hdmi)         shared
- camera (CSI/USB)      split
- Bluetooth controller  shared
- iPhone (Ethernet)     shared
- mic (audio in)        shared
- speaker (audio out)   shared
- led matrix (HUB75)    split
- fan                   ???
- portable battery      split
 */


typedef enum {
    MINBITT_FACE,
    DOOM,
    BADAPPLE,
}cartridge_type;
typedef void (cartridge_t)(blendshapes* blendshapes, float dt, controller_input *controller_input, const connection_t* connection, Image *frontScreenBuf); //TODO: find better home

connection_t parse_args(int argc, char **argv) {
    //TODO:
    // minbitt_hud -m test_recording.txt
    // minbitt_hud 192.160.0.1 49983
    if (argc > 1) {
        connection_t connection;
        connection.type = MOCK;
        connection.path = argv[1];
        return connection;
    } else {
        connection_t face_data;
        face_data.type = PHONE;
        face_data.phone.ip = 0;
        face_data.phone.port = 49983;
        return face_data;
    }
}


int main(int argc, char **argv) {
    // Parsing arguments
    //--------------------------------------------------------------------------------------
    const connection_t connection = parse_args(argc, argv);


    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;//TODO: choose camal case or spline
    const int screenHeight = 720;
    const int FPS = 60;
    const int frontScreenWidth = 64;
    const int frontScreenHeight = 32;
    const int camWidth = 64;
    const int camHeight = 32;
    InitWindow(screenWidth, screenHeight, "minbox");
    // SetExitKey(0);

    Image frontScreenBuf = GenImageColor(frontScreenWidth, frontScreenHeight, BLACK);
    Image cameraBuff = GenImageColor(camWidth, camHeight, BLACK);

    // console system vars
    cartridge_type loaded_cartridge = MINBITT_FACE;
    cartridge_t *cartridge = minbitt_face_cartridge;
    bool show_fps = true;
    bool show_bat = true;
    float dt;
    blendshapes blendshapes;
    SetTargetFPS(FPS);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        get_blendshapes(connection, &blendshapes);
        controller_input controller_input = get_controller_input();
        dt = GetFrameTime();


        // -- load cartaridge --
        //TODO: first unload currenct cartridge
        switch (loaded_cartridge) { //TODO: maybe use function ptr?
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
                DrawText("Error: not valid cartridge", screenWidth/2, screenHeight/2, 20, RED);
                break;
        }



        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawText("MinboX console/OS?", 190, 200, 20, LIGHTGRAY);

            //TODO: display cam feed (maybe make it toggleable by the cartaridge for perf?)
            getCamreaFrame(&cameraBuff);

            // -- running catarage --
             //TODO: maybe seprate update and animat for face cartridge
            cartridge(&blendshapes, dt, &controller_input, &connection, &frontScreenBuf); //TODO: may need to be a Texture instead of Image
            draw_to_front_screen(&frontScreenBuf);

            // -- menu --
            //TODO:

            // -- UI --
            if (show_fps) DrawFPS(10, 10);
            if (show_bat) DrawRectangle(15, screenHeight-40, 100, 20, PINK);


            // -- all editor gui --
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
