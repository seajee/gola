#include "renderer.h"

Renderer::Renderer(
    Game* game,
    int32_t window_width,
    int32_t window_heigth,
    const char* window_title)
    :
    m_Game(game),
    m_WindowWidth(window_width),
    m_WindowHeigth(window_heigth),
    m_WindowTitle(window_title)
{
    m_Window = 0;
    m_Renderer = 0;
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

int32_t Renderer::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    m_Window = SDL_CreateWindow(
        m_WindowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_WindowWidth, m_WindowHeigth,
        0
    );

    if (!m_Window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    if (!m_Renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return 1;
    }

    return 0;
}

void Renderer::Render()
{
    const int32_t cell_width = m_WindowWidth / m_Game->GridWidth;
    const int32_t cell_heigth = m_WindowHeigth / m_Game->GridHeigth;

    for (int32_t y = 0; y < m_Game->GridHeigth; ++y) {
        for (int32_t x = 0; x < m_Game->GridWidth; ++x) {
            if (m_Game->GetCellState(y, x) == CellState::ALIVE) {
                SetColor(255, 255, 255, 255);
            }
            else {
                SetColor(0, 0, 0, 255);
            }

            DrawRect(x * cell_width, y * cell_heigth, cell_width, cell_heigth);
        }
    }

    SDL_RenderPresent(m_Renderer);
    SDL_RenderClear(m_Renderer);
}

void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
}

void Renderer::DrawRect(int32_t x, int32_t y, int32_t width, int32_t heigth)
{
    SDL_Rect rect = {
        x, y,
        width, heigth
    };

    SDL_RenderFillRect(m_Renderer, &rect);
}
