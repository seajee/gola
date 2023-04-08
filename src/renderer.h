#pragma once

#include "common.h"
#include "game.h"

class Renderer
{
public:
    Renderer(
        Game* game,
        int32_t window_width,
        int32_t window_height,
        const char* window_title
    );

    ~Renderer();

    int32_t Init();
    void Render();

private:
    void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void DrawRect(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color);
    void FillSurface(uint32_t color);

private:
    Game* m_Game;
    int32_t m_WindowWidth;
    int32_t m_WindowHeight;
    const char* m_WindowTitle;

    int32_t m_CellWidth;
    int32_t m_CellHeight;

    SDL_Window* m_Window;
    SDL_Surface* m_Surface;
};
