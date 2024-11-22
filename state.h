#ifndef STATE_H_
#define STATE_H_

#include <stdlib.h>

typedef enum { // assume it's int
    INIT = 0,
        START,
        DECK,
        MENU,
        EDIT,
        NEW,
        ENDED,
} ApplicationState;

typedef struct {
    size_t cardIndex;
    size_t size;
} DeckState;

#endif // STATE_H_
