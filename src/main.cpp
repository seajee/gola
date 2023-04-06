#include "common.h"
#include "game.h"
#include "renderer.h"
#include "event.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 800
#define WINDOW_TITLE "gola"

#define GRID_WIDTH 100
#define GRID_HEIGTH 100

#define GAME_DELAY 32

int main(int argc, char** argv)
{
    Game* game = new Game(GRID_WIDTH, GRID_HEIGTH);
    Renderer* renderer = new Renderer(game, WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_TITLE);
    EventManager* event_manager = new EventManager(game);

    if (renderer->Init() != 0) {
        std::cerr << "Failed to initialize a Renderer" << std::endl;
        return 1;
    }

    game->RandomGame();

    while (game->GetState() != GameState::STOP) {
        renderer->Render();
        game->Update();
        event_manager->HandleEvents();

        SDL_Delay(GAME_DELAY);
    }

    delete game;
    delete renderer;
    delete event_manager;

    return 0;
}
