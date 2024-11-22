#include "coords.h"
#include <raylib.h>



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

bool CreateMenu(const float x, const float y, const char *text, const int fontsize, const Color color, const float factor) {
    size_t length = strlen(text);
    Rectangle border = {.x = x, .y = y, .width = length*fontsize*factor, .height = 10.0f + fontsize };
    DrawRectangleLinesEx(border, 3.0f, BLACK);

    // check for hover
    const int mx = GetMouseX(), my = GetMouseY();
    if (CheckCollision(mx, my, border)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) return true;
        unsigned char r,g,b,a;
        r = ClampDown(((long)color.r + 50L), 255L);
        g = ClampDown(((long)color.g + 50L), 255L);
        b = ClampDown(((long)color.b + 50L), 255L);
        a = color.a;
        DrawText(text, x+10, y+5, fontsize, (Color){r,g,b,a});
    } else {
        DrawText(text, x+10, y+5, fontsize, color);
    }
    return false;
}

bool CreateMenuCenter(const char *text, const int fontsize, const Color color, const float factor) {
    float x = WINDOW_WIDTH/2.0f;
    float y = WINDOW_HEIGHT/2.0f;
    size_t length = strlen(text);
    Rectangle border = {.x = x, .y = y, .width = length*fontsize*factor, .height = 10.0f + fontsize };
    Coordinate recalculated = RecalculateCenterRec(border);
    x = recalculated.x;
    y = recalculated.y;
    border.x = x; border.y = y;
    DrawRectangleLinesEx(border, 3.0f, BLACK);

    // check for hover
    const int mx = GetMouseX(), my = GetMouseY();
    if (CheckCollision(mx, my, border)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) return true;
        unsigned char r,g,b,a;
        r = ClampDown(((long)color.r + 50L), 255L);
        g = ClampDown(((long)color.g + 50L), 255L);
        b = ClampDown(((long)color.b + 50L), 255L);
        a = color.a;
        DrawText(text, x+10, y+5, fontsize, (Color){r,g,b,a});
    } else {
        DrawText(text, x+10, y+5, fontsize, color);
    }
    return false;
}


size_t DeckSelector(const float x, const float y, const char **deckTitles, const size_t decksTotal, const int fontsize, const Color color, const float factor) {

    size_t maxLength = 0;
    for (size_t i = 0; i < decksTotal; i++) {
        size_t length = strlen(deckTitles[i]);
        if (length > maxLength) {
            maxLength = length;
        }
    }
    const Rectangle viewBounds = {.x = x, .y = y, .width = maxLength*factor, .height=fontsize*1.1*decksTotal};

    DrawRectangleLinesEx((Rectangle){.x = viewBounds.x-5, .y = viewBounds.y-5, .width = viewBounds.width+10, .height = viewBounds.height+10}, 3.0f, color);

    for (size_t i = 0; i < decksTotal; i++) {
        int mx = GetMouseX(), my = GetMouseY(); // Mouse X and Mouse Y
        const char *title = deckTitles[i];
        const Rectangle textBounds = (Rectangle){.x = viewBounds.x+3, .y = viewBounds.y + fontsize*1.1*i, .width = maxLength*factor, .height=fontsize*1.1};
        DrawText(title, viewBounds.x+3, viewBounds.y + fontsize*1.1*i, fontsize, color);
        if (CheckCollision(mx, my, textBounds)) {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) return i;
            DrawRectangleRec(textBounds, (Color){.r = 57, .g = 219, .b = 247, .a = 20});
        }
    }

    return -1;
}
