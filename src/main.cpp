#include "common.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 800
#define WINDOW_TITLE "gola"

#define GRID_WIDTH 100
#define GRID_HEIGTH 100

#define CELL_WIDTH WINDOW_WIDTH / GRID_WIDTH
#define CELL_HEIGTH WINDOW_HEIGTH / GRID_HEIGTH

int main(int argc, char** argv)
{
    std::srand(std::time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGTH,
        0
    );

    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int32_t y = 0; y < GRID_HEIGTH; ++y) {
            for (int32_t x = 0; x < GRID_WIDTH; ++x) {
                int32_t r = std::rand() % 256;
                int32_t g = std::rand() % 256;
                int32_t b = std::rand() % 256;
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);

                SDL_Rect rect = {
                    CELL_WIDTH * x,
                    CELL_HEIGTH * y,
                    CELL_WIDTH,
                    CELL_HEIGTH
                };

                SDL_RenderFillRect(renderer, &rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
