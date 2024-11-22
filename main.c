        /*
  /     \  \_____  \| | \__    ___/|  |__   ____   \_____  \  __ __|__|______|  |   _____/  |_  \______   \ ____ ______ |  | _____    ____  ____   _____   ____   _____/  |_| |
 /  \ /  \  /  / \  \ |   |    |   |  |  \_/ __ \   /  / \  \|  |  \  \___   /  | _/ __ \   __\  |       _// __ \\____ \|  | \__  \ _/ ___\/ __ \ /     \_/ __ \ /    \   __\ |
/    Y    \/   \_/.  \|   |    |   |   Y  \  ___/  /   \_/.  \  |  /  |/    /|  |_\  ___/|  |    |    |   \  ___/|  |_> >  |__/ __ \\  \__\  ___/|  Y Y  \  ___/|   |  \  |  \|
\____|__  /\_____\ \_/_   |____|   |___|  /\___  > \_____\ \_/____/|__/_____ \____/\___  >__|    |____|_  /\___  >   __/|____(____  /\___  >___  >__|_|  /\___  >___|  /__|  __
        \/        \__>/                 \/     \/         \__>              \/         \/               \/     \/|__|             \/     \/    \/      \/     \/     \/      \/
         */
#include "coords.h"
#include "state.h"
#include "asciiart.h"
#include <raylib.h>

int main(void)
{
    fprintf(stderr, "MQ!\n");
    fprintf(stderr, "%s\n", ascii_art);

    SetTargetFPS(30);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MQ");
    InitAudioDevice();
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    Music bgm1 = LoadMusicStream("resources/effect.ogg");
    SetMasterVolume(69);
    PlayMusicStream(bgm1);

    Sound hoverSound = LoadSound("resources/select.ogg");

    ApplicationState state = INIT;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Q)) state = ENDED;
        if (IsKeyPressed(KEY_ESCAPE)) state = ENDED;
        switch (state) {
            case INIT:
                state = START;
                break;
            case START:
                ClearBackground(RAYWHITE);
                UpdateMusicStream(bgm1);

                BeginDrawing();
                if (CreateMenuCenter("START", 65, BLACK, 0.80f)) {
                    state = MENU;
                }
                EndDrawing();
                break;
            case MENU:
                ClearBackground(RAYWHITE);
                UpdateMusicStream(bgm1);
                BeginDrawing();

                bool menus[] = {
                    CreateMenu(30, 30, "Load Deck", 40, BLACK, 0.65),
                    CreateMenu(30, 90, "Create New Deck", 40, BLACK, 0.65),
                    CreateMenu(30, 150, "Edit Deck", 40, BLACK, 0.65),
                    CreateMenu(30, 210, "BACK", 40, BLACK, 0.95),
                };
                const size_t menu_back_index = 3;
                const size_t menu_deck_index = 0;

                if (menus[menu_back_index]) {
                    state = START;
                }

                if (menus[menu_deck_index]) {
                    state = DECK;
                }

                EndDrawing();
                break;
            case DECK:
                ClearBackground(RAYWHITE);
                BeginDrawing();


                if (CreateMenu(30, 390, "Quit", 40 ,BLACK, 0.65)) {
                    state = MENU;
                }

                const char *titles[] = {"Hello", "World", "LOL", "Meine", "Freunde"};
                const size_t titlesSize = 5;
                /* const Rectangle bounds = {.x = 20, .y = 20, .width = 100, .height = 100}; */
                /* size_t _ = DeckView(&titles[0], titlesSize, bounds, 20, BLACK, 0.6); */

                size_t res = DeckSelector(20, 20, titles, titlesSize, 25, BLACK, 21.2f);
                if (res != (size_t)-1) {
                    fprintf(stderr, "Clicked ID: %zu\n", res);

                }

                EndDrawing();
                break;
            case ENDED:
            default:
                goto EXIT;
                break;
        };
    }

EXIT:
    StopMusicStream(bgm1);
    UnloadMusicStream(bgm1);
    UnloadSound(hoverSound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
