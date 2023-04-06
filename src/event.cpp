#include "event.h"
#include "game.h"

EventManager::EventManager(Game* game) :
    m_Game(game)
{
    m_Event = {};
}

void EventManager::HandleEvents()
{
    while (SDL_PollEvent(&m_Event) != 0) {
        switch (m_Event.type) {
        case SDL_QUIT:
            m_Game->SetState(GameState::STOP);
            break;

        // TODO: Associate keys in a config file
        case SDL_KEYDOWN:
            switch (m_Event.key.keysym.scancode) {
            case SDL_SCANCODE_P:
                if (m_Game->GetState() == GameState::PAUSE) {
                    m_Game->SetState(GameState::RUN);
                }
                else {
                    m_Game->SetState(GameState::PAUSE);
                }
                break;
            case SDL_SCANCODE_R:
                m_Game->RandomGame();
                break;
            case SDL_SCANCODE_Q:
                m_Game->SetState(GameState::STOP);
                break;
            }
            break;
        /*
        case SDL_KEYUP:
            break;
        */
        }
    }
}