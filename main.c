#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <raylib.h>
#include <string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

#define MAIN_MENU_OPTION_COUNT 4

bool CheckCollision(float posx,
                    float posy,
                    Rectangle rec) {
    float recx, recy, sizex, sizey;
    recx = rec.x;
    recy = rec.y;
    sizex = rec.width;
    sizey = rec.height;

    const float limitx = recx + sizex;
    const float limity = recy + sizey;

    if (posx > recx && posx < limitx) {
        if (posy > recy && posy < limity) {
            return true;
        }
    }
    return false;
}


const char *boolStr(bool input) {
    if (input) return "YES";
    return "NO";
}

typedef struct {
    float x, y;
} Coordinate;

Coordinate *PlaceTexts(const char **titles, const size_t numTitles, const Color *colors, const int fontsize) {
    Coordinate *coordinates = (Coordinate *)calloc(sizeof(Coordinate), numTitles);
    for (size_t i = 0 ; i < numTitles; i++) {
        const char *title = titles[i];
        const size_t t_size = strlen(title);
        DrawText(title, WINDOW_WIDTH/2 - (t_size * 7), WINDOW_HEIGHT/2 - (numTitles-i)*(fontsize+20), fontsize, colors[i]);
        coordinates[i] = (Coordinate){.x = WINDOW_WIDTH/2.0f - (t_size * 7), .y = WINDOW_HEIGHT/2.0f - (numTitles-i)*(fontsize+20)};
    }
    return coordinates;
}

Rectangle GetTextBoundingBox(const char *title, const int fontsize, Coordinate coord) {
    float x, y;
    x = coord.x-5;
    y = coord.y-5;
    float w, h;
    w = strlen(title) * 14.0f + 10;
    h = fontsize+10;

    return (Rectangle){.x = x, .y = y, .width = w, .height = h};
}

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
    /* Sound clickSound = LoadSound("resources/click.ogg"); */


    const char *titles[MAIN_MENU_OPTION_COUNT] = {"Main Menu", "Open Set File", "Edit Set File", "Quit"};
    const Color titleColors[MAIN_MENU_OPTION_COUNT] = {{0,0,0,255}, {100,100,100,255}, {100, 100, 100, 255}, {0,0,0,255}};
    const Color dimmedTitleColors[MAIN_MENU_OPTION_COUNT] = {{30,30,30,255}, {130,130,130,255}, {130, 130, 130, 255}, {30,30,30,255}};
    /* const float rect_width = 50.0f; */
    /* const float rect_height = 50.0f; */

    bool hoverings[MAIN_MENU_OPTION_COUNT] = {false, false, false, false};
    bool clicks[MAIN_MENU_OPTION_COUNT] = {false, false, false, false};

    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        UpdateMusicStream(bgm1);

        BeginDrawing();
        
        const int mousex = GetMouseX();
        const int mousey = GetMouseY();

        bool thereareclicks = false;
        for (size_t i = 0; i < MAIN_MENU_OPTION_COUNT; i++) {
            thereareclicks |= clicks[i];
        }
        if (thereareclicks) {
            for (size_t i = 0; i < MAIN_MENU_OPTION_COUNT; i++) {
                switch (i) {
                    case 0:
                        clicks[i] = false;
                        break;
                    case 1:
                        if (clicks[i]) {
                            fprintf(stderr, "yeah! 1\n");
                            if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
                                clicks[i] = false;
                            }
                        }
                        break;
                    case 2:
                        if (clicks[i]) {
                            fprintf(stderr, "yeah! 2\n");
                            if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
                                clicks[i] = false;
                            }
                        }
                        break;
                    case 3:
                        if (clicks[i])
                            goto BREAKOUT;
                }
            }
        } else {
            const Color *selector = &titleColors[0];
            Coordinate *coords = PlaceTexts(titles, MAIN_MENU_OPTION_COUNT, selector, 25);
            Rectangle boxes[MAIN_MENU_OPTION_COUNT];
            for (size_t i = 0; i < MAIN_MENU_OPTION_COUNT; i++) {
                boxes[i] = GetTextBoundingBox(titles[i], 25, coords[i]);
                DrawRectangleLinesEx(boxes[i], 2.0f, (Color){20,20,20,255});
                if (CheckCollision(mousex, mousey, boxes[i])) {
                    fprintf(stderr, "In\n");
                    if (!hoverings[i]) {
                        PlaySound(hoverSound);
                        selector = &dimmedTitleColors[0];
                    }
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                        clicks[i] = true;
                    }
                    hoverings[i] = true;
                } else {
                    hoverings[i] = false;
                    selector = &titleColors[0];
                    fprintf(stderr, "Out\n");
                }
            }

            free(coords);
        }

        if (IsKeyPressed(KEY_Q)) break;
        if (IsKeyPressed(KEY_ESCAPE)) break;

        EndDrawing();
    }

BREAKOUT:
    StopMusicStream(bgm1);
    UnloadMusicStream(bgm1);
    UnloadSound(hoverSound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
