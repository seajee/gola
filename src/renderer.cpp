#include "renderer.h"

Renderer::Renderer(
    Game* game,
    int32_t window_width,
    int32_t window_height,
    const char* window_title)
    :
    m_Game(game),
    m_WindowWidth(window_width),
    m_WindowHeight(window_height),
    m_WindowTitle(window_title)
{
    m_Window = 0;

    m_CellWidth = m_WindowWidth / m_Game->GridWidth;
    m_CellHeight = m_WindowHeight / m_Game->GridHeight;
}

Renderer::~Renderer()
{
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
        m_WindowWidth, m_WindowHeight,
        0
    );

    if (!m_Window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    m_Surface = SDL_GetWindowSurface(m_Window);

    if (!m_Surface) {
        SDL_Log("Failed to get surface: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    FillSurface(SDL_MapRGBA(m_Surface->format, 0, 0, 0, 255));

    return 0;
}

void Renderer::Render()
{
    if (m_Game->GetState() != GameState::RUN) {
        return;
    }

    for (int32_t y = 0; y < m_Game->GridHeight; ++y) {
        for (int32_t x = 0; x < m_Game->GridWidth; ++x) {
            if (!m_Game->CellChanged(x, y)) {
                continue;
            }

            uint32_t color = SDL_MapRGBA(m_Surface->format, 0, 0, 0, 255);

            if (m_Game->GetCell(x, y) == CellState::ALIVE) {
                color = SDL_MapRGBA(m_Surface->format, 255, 255, 255, 255);
            }

            DrawRect(x * m_CellWidth, y * m_CellHeight, m_CellWidth, m_CellHeight, color);
        }
    }

    SDL_UpdateWindowSurface(m_Window);
}


void Renderer::DrawRect(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color)
{
    SDL_Rect rect = {
        x, y,
        width, height
    };

    SDL_FillRect(m_Surface, &rect, color);
}

void Renderer::FillSurface(uint32_t color)
{
    SDL_LockSurface(m_Surface);
    SDL_memset(m_Surface->pixels, color, m_Surface->h * m_Surface->pitch);
    SDL_UnlockSurface(m_Surface);
}
