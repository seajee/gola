#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define WINDOW_TITLE "gola"

#define GRID_WIDTH 500
#define GRID_HEIGTH 500

#define GAME_DELAY 16
#define GAME_SEED 69

#include "app.h"

int main()
{
    Application app(
        WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,
        GRID_WIDTH, GRID_HEIGTH,
        GAME_DELAY, GAME_SEED
    );

    int32_t result = app.Run();

    return result;
}
