#include "coords.h"

int main(void)
{
    fprintf(stderr, "MQ!");


    SetTargetFPS(30);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MQ");
    InitAudioDevice();
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    Music bgm1 = LoadMusicStream("resources/effect.ogg");
    SetMasterVolume(50);
    PlayMusicStream(bgm1);

    Sound hoverSound = LoadSound("resources/select.ogg");

    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        UpdateMusicStream(bgm1);

        BeginDrawing();

        CreateMenu(50, 50, "Hello World", 55, BLACK);

        if (IsKeyPressed(KEY_Q)) break;
        if (IsKeyPressed(KEY_ESCAPE)) break;

        EndDrawing();
    }

    StopMusicStream(bgm1);
    UnloadMusicStream(bgm1);
    UnloadSound(hoverSound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
