#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <raylib.h>
#include <string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

#define MAIN_MENU_OPTION_COUNT 4

typedef struct {
    float x, y;
} Coordinate;
Coordinate RecalculateCenterXYWH(float x, float y, float width, float height);
Coordinate RecalculateCenterRec(Rectangle rec);
bool CheckCollision(float posx, float posy, Rectangle rec);
const char *boolStr(bool input);
Rectangle GetTextBoundingBox(const char *title, const int fontsize, Coordinate coord);
unsigned char ClampDown(const long _a, const long _b);
bool CreateMenu(const float x, const float y, const char *text, const int fontsize, const Color color, const float factor);
bool CreateMenuCenter(const char *text, const int fontsize, const Color color, const float factor);


size_t DeckSelector(const float x, const float y, const char **deckTitles, const size_t decksTotal, const int fontsize, const Color color, const float factor, Rectangle *clickedTextBounds);


#endif // MAIN_H_
