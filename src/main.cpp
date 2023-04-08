#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "gola"

#define GRID_WIDTH WINDOW_WIDTH
#define GRID_HEIGHT WINDOW_HEIGHT

#define GAME_DELAY 16
#define GAME_SEED 69

#include "app.h"

int main()
{
    Application app(
        WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,
        GRID_WIDTH, GRID_HEIGHT,
        GAME_DELAY, GAME_SEED
    );

    int32_t result = app.Run();

    return result;
}
