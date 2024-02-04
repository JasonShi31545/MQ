#include "quiz.h"
#include "welcome.h"
#include "raylib.h"
using namespace std;

int main(int argc, const char *argv[]) {

    printf("Start Program\n");

    const int width = 800;
    const int height = 550;

    SetTargetFPS(144);
    InitWindow(width, height, "MQ");
    InitAudioDevice();
    SetConfigFlags(FLAG_MSAA_4X_HINT);


    // Sound
    Music bgm1 = LoadMusicStream("resources/effect.ogg");
    SetMasterVolume(50);
    PlayMusicStream(bgm1);

    Sound hoverSound = LoadSound("resources/select.ogg");
    Sound clickSound = LoadSound("resources/click.ogg");
    bool hovers = false;
    bool hovers2 = false;
    bool clicked = false;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_Q)) {
            break;
        }
        UpdateMusicStream(bgm1);

        if (!clicked) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("MQ: Learning Sets", width/2 - (110), height / 5, 22, BLACK);
            DrawText("Begin", width / 2 - 25, height / 2, 22, hovers ? Fade(BLACK, 0.5f) : BLACK);
            DrawText("Quit", width / 2 - 25, height / 2 + 30, 22, hovers2 ? Fade(BLACK, 0.5f) : BLACK);
            EndDrawing();

            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){width/2 - 25,height/2 + 30,40,20})) {
                if (!hovers2) {
                    PlaySound(hoverSound);
                }
                hovers2 = true;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    break;
                }
            } else {
                hovers2 = false;
            }
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){width/2 - 25,height/2,40,20})) {
                if (!hovers) {
                    PlaySound(hoverSound);
                }
                hovers = true;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    printf("Clicked!\n");
                    clicked = true;
                    PlaySound(clickSound);
                }
            } else {
                hovers = false;
            }

        } else {
            // display(width, height);
            goto DISP;

        }
    }
    goto END;
DISP:
    display(width, height);


END:

    StopMusicStream(bgm1);
    UnloadMusicStream(bgm1);
    UnloadSound(hoverSound);
    UnloadSound(clickSound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
