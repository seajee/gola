#include "common.h"
#include "game.h"
#include "cell.h"

Game::Game(int32_t grid_width, int32_t grid_height) :
    GridWidth(grid_width), GridHeight(grid_height),
    m_FrontGrid(grid_width, grid_height),
    m_BackGrid(grid_width, grid_height)
{
    m_CurrentGrid = &m_FrontGrid;
    m_OtherGrid = &m_BackGrid;
    m_State = GameState::RUN;

    for (int32_t y = 0; y < GridHeight; ++y) {
        for (int32_t x = 0; x < GridWidth; ++x) {
            SetCell(m_CurrentGrid, x, y, CellState::DEAD);
        }
    }
}

GameState Game::GetState()
{
    return m_State;
}

void Game::SetState(GameState state)
{
    m_State = state;
}

CellState Game::GetCell(int32_t x, int32_t y)
{
    return GetCell(m_CurrentGrid, x, y);
}

bool Game::CellChanged(int32_t x, int32_t y)
{
    return GetCell(m_CurrentGrid, x, y) != GetCell(m_OtherGrid, x, y);
}

void Game::RandomGame()
{
    for (int32_t y = 0; y < GridHeight; ++y) {
        for (int32_t x = 0; x < GridWidth; ++x) {
            CellState result = (std::rand() % 2) ? CellState::ALIVE : CellState::DEAD;
            SetCell(m_CurrentGrid, x, y, result);
            SetCell(m_OtherGrid, x, y, result);
        }
    }
}

void Game::Update()
{
    if (m_State != GameState::RUN) {
        return;
    }

    for (int32_t y = 0; y < GridHeight; ++y) {
        for (int32_t x = 0; x < GridWidth; ++x) {
            int32_t nb = CountNeighbors(x, y);
            CellState cs = GetCell(m_CurrentGrid, x, y);
            CellState next_state = CellState::DEAD;

            if (cs == CellState::ALIVE && (nb == 3 || nb == 2)) {
                next_state = CellState::ALIVE;
            }
            else if (cs == CellState::DEAD && nb == 3) {
                next_state = CellState::ALIVE;
            }

            SetCell(m_OtherGrid, x, y, next_state);
        }
    }

    CellGrid* temp = m_CurrentGrid;
    m_CurrentGrid = m_OtherGrid;
    m_OtherGrid = temp;
}


int32_t Game::CountNeighbors(int32_t x, int32_t y)
{
    static const int32_t offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, +1},
        { 0, -1},          { 0, +1},
        {+1, -1}, {+1, 0}, {+1, +1}
    };

    int32_t count = 0;

    for (int32_t i = 0; i < 8; ++i) {
        if (GetCell(m_CurrentGrid, x + offsets[i][0], y + offsets[i][1]) == CellState::ALIVE) {
            ++count;
        }
    }

    return count;
}

CellState Game::GetCell(CellGrid* grid, int32_t x, int32_t y)
{
    if (x > GridWidth - 1)
        x -= GridWidth;
    else if (x < 0)
        x = GridWidth + x;

    if (y > GridHeight - 1)
        y -= GridHeight;
    else if (y < 0)
        y = GridHeight + y;

    return (*grid)[y][x];
}

void Game::SetCell(CellGrid* grid, int32_t x, int32_t y, CellState state)
{
    if (x > GridWidth - 1)
        x -= GridWidth;
    else if (x < 0)
        x = GridWidth + x;

    if (y > GridHeight - 1)
        y -= GridHeight;
    else if (y < 0)
        y = GridHeight + y;

    (*grid)[y][x] = state;
}
