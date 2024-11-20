#include "coords.h"



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

Coordinate RecalculateCenterXYWH(float x, float y, float width, float height) {
    return (Coordinate){.x = (x - width/2.0f), .y = (y - height/2.0f)};
}
Coordinate RecalculateCenterRec(Rectangle rec) {
    return (Coordinate){.x = (rec.x - rec.width/2.0f), .y = (rec.y - rec.height/2.0f)};
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

unsigned char ClampDown(const long _a, const long _b) {
    long a = (long)_a;
    long b = (long)_b;
    if (a < b) {
        return (unsigned char)a;
    }
    return (unsigned char) b;
}

void CreateMenu(const float x, const float y, const char *text, const int fontsize, const Color color) {
    size_t length = strlen(text);
    Rectangle border = {.x = x, .y = y, .width = length*fontsize*MENU_TEXTBOX_SCALE_FACTOR, .height = 10.0f + fontsize };
    DrawRectangleLinesEx(border, 3.0f, BLACK);

    // check for hover
    const int mx = GetMouseX(), my = GetMouseY();
    if (CheckCollision(mx, my, border)) {
        unsigned char r,g,b,a;
        r = ClampDown(((long)color.r + 50L), 255L);
        g = ClampDown(((long)color.g + 50L), 255L);
        b = ClampDown(((long)color.b + 50L), 255L);
        a = color.a;
        DrawText(text, x+10, y+5, fontsize, (Color){r,g,b,a});
    } else {
        DrawText(text, x+10, y+5, fontsize, color);
    }
}

void CreateMenuCenter(const char *text, const int fontsize, const Color color) {
    const float x = WINDOW_WIDTH/2.0f;
    const float y = WINDOW_HEIGHT/2.0f;
    size_t length = strlen(text);
    Rectangle border = {.x = x, .y = y, .width = length*fontsize*MENU_TEXTBOX_SCALE_FACTOR, .height = 10.0f + fontsize };
    Coordinate recalculated = RecalculateCenterRec(border);
    border.x = recalculated.x;
    border.y = recalculated.y;
    DrawRectangleLinesEx(border, 3.0f, BLACK);

    // check for hover
    const int mx = GetMouseX(), my = GetMouseY();
    if (CheckCollision(mx, my, border)) {
        unsigned char r,g,b,a;
        r = ClampDown(((long)color.r + 50L), 255L);
        g = ClampDown(((long)color.g + 50L), 255L);
        b = ClampDown(((long)color.b + 50L), 255L);
        a = color.a;
        DrawText(text, x+10, y+5, fontsize, (Color){r,g,b,a});
    } else {
        DrawText(text, x+10, y+5, fontsize, color);
    }
}
