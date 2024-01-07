#include <iostream>
#include <map>
#include <unordered_map>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <chrono>
#include <queue>
#include <ctime>
#include <optional>
#include <SDL2/SDL.h>

#ifndef QUIZ_H
#define QUIZ_H

typedef enum: int {
    TD = 0,
    DT = 1,
} Direction;

typedef struct {
    std::string term;
    std::string def;
    unsigned int mastery;
    unsigned int corrects;
    unsigned int mistakes;
    std::optional<std::chrono::duration<double>> elapsed_correct;
} Item;

struct Set {
    Item *items;
    size_t size;
    std::optional<std::chrono::duration<double>> elapsed_open;
    Set() {
        items = nullptr;
        size = 0;
        elapsed_open = std::nullopt;
    }
};

class MCQ{
public:
        Item choices[4];
        int correctID;
        Direction direction;
        MCQ() : choices(), correctID(0), direction(TD) {}

};
class ERQ {
public:
        std::string response;
        Item correctItem;
        ERQ() : response(""), correctItem({0}) {}
};




#endif // QUIZ_H
