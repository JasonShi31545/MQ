#include "quiz.h"
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
    float offset = 0.0f;

    const float RECT_WIDTH = 200;
    const float RECT_HEIGHT = 100;

    // Sound
    Music bgm = LoadMusicStream("resources/effect.ogg");
    PlayMusicStream(bgm);

    Sound hoverSound = LoadSound("resources/select.ogg");

    bool rect_hovers[4] = {false, false, false, false};

    Rectangle rect1;
    Rectangle rect2;
    Rectangle rect3;
    Rectangle rect4;
    Rectangle *rects[4] = {&rect1, &rect2, &rect3, &rect4};
    Color colours[4] = {RED, GREEN, YELLOW, BLUE};

    int mouseClickID = -1;
    char a[20] = "Default";
    int text_x = 0, text_y = 0;
    while (!WindowShouldClose()) {
        rect1 = {width / 2 - RECT_WIDTH - 5,height / 2, RECT_WIDTH, RECT_HEIGHT - offset};
        rect2 = {width / 2,height / 2, RECT_WIDTH - offset, RECT_HEIGHT};
        rect3 = {width / 2,height / 2 + (RECT_HEIGHT + 5), RECT_WIDTH + offset, RECT_HEIGHT};
        rect4 = {width / 2 - RECT_WIDTH - 5,height / 2 + (RECT_HEIGHT + 5), RECT_WIDTH + offset, RECT_HEIGHT};
        UpdateMusicStream(bgm);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("MQ: Learning Sets", width/2 - (RECT_HEIGHT + 5), height / 5, 22, BLACK);

            for (int i = 0; i < 4; i++) {
                DrawRectangleRounded(*rects[i], 0.45, 10, rect_hovers[i] ?  Fade(colours[i], 0.8f) : colours[i]);
            }

            if (mouseClickID != -1) {
                sprintf(a, "Clicked %d", mouseClickID);
                text_x = rects[mouseClickID]->x;
                text_y = rects[mouseClickID]->y;
            }
            DrawText(a, text_x, text_y, 22, BLACK);
        EndDrawing();
        if (IsKeyDown(KEY_Q)) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            if (CheckCollisionPointRec(GetMousePosition(), *rects[i])) {
                if (!rect_hovers[i]) {
                    PlaySound(hoverSound);
                }
                rect_hovers[i] = true;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    mouseClickID = i;
                } else {
                    mouseClickID = -1;
                }
            } else {
                rect_hovers[i] = false;
            }
        }
        offset = 5.5f*sinf(GetTime());
    }
    StopMusicStream(bgm);
    UnloadMusicStream(bgm);
    UnloadSound(hoverSound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
