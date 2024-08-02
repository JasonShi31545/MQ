#include <raylib.h>

void display(const float width, const float height) {
    const float RECT_WIDTH = 200;
    const float RECT_HEIGHT = 100;

    float offset = 0.0f;
    Rectangle rect1, rect2, rect3, rect4;
    Rectangle *rects[4] = {&rect1, &rect2, &rect3, &rect4};
    Color colours[4] = {RED, GREEN, YELLOW, BLUE};
    bool rect_hovers[4] = {false, false, false, false};
    int mouseClickID = -1;
    int keyboardID = -1;
    char a[20] = "";
    int text_x = 0, text_y = 0;
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_Q)) {
            break;
        }
        rect1 = {width / 2 - RECT_WIDTH - 5,height / 2, RECT_WIDTH, RECT_HEIGHT - offset};
        rect2 = {width / 2,height / 2, RECT_WIDTH - offset, RECT_HEIGHT};
        rect3 = {width / 2,height / 2 + (RECT_HEIGHT + 5), RECT_WIDTH + offset, RECT_HEIGHT};
        rect4 = {width / 2 - RECT_WIDTH - 5,height / 2 + (RECT_HEIGHT + 5), RECT_WIDTH + offset, RECT_HEIGHT};

        if (IsKeyDown(KEY_ONE) || IsKeyDown(KEY_KP_1)) {
            keyboardID = 0;
            sprintf(a, "Keyboard selected %d", keyboardID);
        }
        if (IsKeyDown(KEY_TWO) || IsKeyDown(KEY_KP_2)) {
            keyboardID = 1;
            sprintf(a, "Keyboard selected %d", keyboardID);
        }

        if (IsKeyDown(KEY_THREE) || IsKeyDown(KEY_KP_3)) {
            keyboardID = 2;
            sprintf(a, "Keyboard selected %d", keyboardID);
        }

        if (IsKeyDown(KEY_FOUR) || IsKeyDown(KEY_KP_4)) {
            keyboardID = 3;
            sprintf(a, "Keyboard selected %d", keyboardID);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

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


        for (int i = 0; i < 4; i++) {
            if (CheckCollisionPointRec(GetMousePosition(), *rects[i])) {
                // if (!rect_hovers[i]) {
                //     PlaySound(hoverSound);
                // }
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
}
