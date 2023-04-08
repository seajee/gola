#include "app.h"

Application::Application(
    int32_t window_width, int32_t window_height, const char* window_title,
    int32_t grid_width, int32_t grid_height,
    int32_t game_delay, int32_t seed)
    :
    m_GameDelay(game_delay)
{
    std::srand(seed);

    m_Game = new Game(grid_width, grid_height);
    m_Renderer = new Renderer(m_Game, window_width, window_height, window_title);
    m_EventManager = new EventManager(m_Game);
}

Application::~Application()
{
    delete m_Game;
    delete m_Renderer;
    delete m_EventManager;
}

int32_t Application::Run()
{
    if (m_Renderer->Init() != 0) {
        std::cerr << "Failed to initialize a Renderer" << std::endl;
        return 1;
    }

    m_Game->RandomGame();

    while (m_Game->GetState() != GameState::STOP) {
        m_Renderer->Render();
        m_Game->Update();
        m_EventManager->HandleEvents();

        SDL_Delay(m_GameDelay);
    }

    return 0;
}
