#include "common.h"
#include "game.h"
#include "renderer.h"
#include "event.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGTH 1000
#define WINDOW_TITLE "gola"

#define GRID_WIDTH 500
#define GRID_HEIGTH 500

#define GAME_DELAY 16
#define GAME_SEED 69

int main(int argc, char** argv)
{
    std::srand(GAME_SEED);

    Game game = Game(GRID_WIDTH, GRID_HEIGTH);
    Renderer renderer = Renderer(&game, WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_TITLE);
    EventManager event_manager = EventManager(&game);

    if (renderer.Init() != 0) {
        std::cerr << "Failed to initialize a Renderer" << std::endl;
        return 1;
    }

    game.RandomGame();

    while (game.GetState() != GameState::STOP) {
        renderer.Render();
        game.Update();
        event_manager.HandleEvents();

        SDL_Delay(GAME_DELAY);
    }

    return 0;
}
