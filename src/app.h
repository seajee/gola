#pragma once

#include "common.h"
#include "game.h"
#include "renderer.h"
#include "event.h"

class Application
{
public:
    Application(
        int32_t window_width, int32_t window_height, const char* window_title,
        int32_t grid_width, int32_t grid_height,
        int32_t game_delay, int32_t seed);
    
    ~Application();

    int32_t Run();

private:
    Game* m_Game;
    Renderer* m_Renderer;
    EventManager* m_EventManager;

    int32_t m_GameDelay;
};
