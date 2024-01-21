#include "quiz.h"
#include <raylib.h>
using namespace std;

int main(int argc, const char *argv[]) {

    printf("Start Program\n");

    const int width = 800;
    const int height = 550;

    SetTargetFPS(144);
    InitWindow(width, height, "MQ");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    float offset = 0.0f;

    const float RECT_WIDTH = 200;
    const float RECT_HEIGHT = 100;

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("MQ: Learning Sets", width/2 - (RECT_HEIGHT + 5), height / 5, 22, BLACK);
            DrawRectangleRounded({width / 2 - RECT_WIDTH - 5,height / 2, RECT_WIDTH, RECT_HEIGHT - offset}, 0.45, 10, RED);
            DrawRectangleRounded({width / 2,height / 2, RECT_WIDTH - offset, RECT_HEIGHT}, 0.45, 10, GREEN);
            DrawRectangleRounded({width / 2,height / 2 + (RECT_HEIGHT + 5), RECT_WIDTH + offset, RECT_HEIGHT}, 0.45, 10, YELLOW);
            DrawRectangleRounded({width / 2 - RECT_WIDTH - 5,height / 2 + (RECT_HEIGHT + 5), RECT_WIDTH + offset, RECT_HEIGHT}, 0.45, 10, BLUE);
        EndDrawing();
        if (IsKeyDown(KEY_Q)) {
            break;
        }
        offset = 5.5f*sinf(GetTime());
    }
    CloseWindow();

    return 0;
}
