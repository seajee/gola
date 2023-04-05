#include "common.h"
#include "game.h"
#include "renderer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 800
#define WINDOW_TITLE "gola"

#define GRID_WIDTH 200
#define GRID_HEIGTH 200

int main(int argc, char** argv)
{
    Game game(GRID_WIDTH, GRID_HEIGTH);
    Renderer renderer(&game, WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_TITLE);

    if (renderer.Init() != 0) {
        std::cerr << "Failed to initialize a Renderer" << std::endl;
        return 1;
    }

	game.RandomGame();

    bool quit = false;
    while (!quit) {
        renderer.Render();
        game.Next();

        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_Delay(16);
    }

    return 0;
}
