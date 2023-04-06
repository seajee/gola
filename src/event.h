#pragma once

#include "common.h"
#include "game.h"

class EventManager
{
public:
    EventManager(Game* game);
    void HandleEvents();

private:
    Game* m_Game;
    SDL_Event m_Event;
};
