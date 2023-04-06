#include "game.h"
#include "common.h"

Game::Game(int32_t grid_width, int32_t grid_height) :
    GridWidth(grid_width), GridHeight(grid_height),
    m_FrontGrid(grid_width, grid_height),
    m_BackGrid(grid_width, grid_height)
{
    m_CurrentGrid = &m_FrontGrid;
    m_OtherGrid = &m_BackGrid;
    m_State = GameState::RUN;
}

CellState Game::GetCellState(int32_t x, int32_t y)
{
    if (x > GridWidth - 1)
        x -= GridWidth;
    else if (x < 0)
        x = GridWidth + x;

    if (y > GridHeight - 1)
        y -= GridHeight;
    else if (y < 0)
        y = GridHeight + y;

    return (*m_CurrentGrid)[y][x];
}

void Game::RandomGame()
{
    std::srand((uint32_t)std::time(NULL));

    // TODO: create a funtion to copy a Matrix2D
    for (int32_t y = 0; y < GridHeight; ++y) {
        for (int32_t x = 0; x < GridWidth; ++x) {
            CellState result = (std::rand() % 2) ? CellState::ALIVE : CellState::DEAD;
            SetCell(m_CurrentGrid, y, x, result);
            SetCell(m_OtherGrid, y, x, result);
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

void Game::Update()
{
    if (m_State != GameState::RUN) {
        return;
    }

    for (int32_t y = 0; y < GridHeight; ++y) {
        for (int32_t x = 0; x < GridWidth; ++x) {
            int32_t nb = CountAliveNeighbors(x, y);
            CellState cs = GetCellState(x, y);

            if (cs == CellState::ALIVE && (nb < 2 || nb > 3)) {
                SetCell(m_OtherGrid, x, y, CellState::DEAD);
            }
            else if (cs == CellState::ALIVE && (nb == 3 || nb == 2)) {
                SetCell(m_OtherGrid, x, y, CellState::ALIVE);
            }
            else if (cs == CellState::DEAD && nb == 3) {
                SetCell(m_OtherGrid, x, y, CellState::ALIVE);
            }
            else {
                SetCell(m_OtherGrid, x, y, CellState::DEAD);
            }
        }
    }

    Matrix2D<CellState>* temp = m_CurrentGrid;
    m_CurrentGrid = m_OtherGrid;
    m_OtherGrid = temp;
}

int32_t Game::CountAliveNeighbors(int32_t x, int32_t y)
{
    static const int32_t offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, +1},
        { 0, -1},          { 0, +1},
        {+1, -1}, {+1, 0}, {+1, +1}
    };

    int32_t count = 0;

    for (int32_t i = 0; i < 8; ++i) {
        if (GetCellState(x + offsets[i][0], y + offsets[i][1]) == CellState::ALIVE) {
            ++count;
        }
    }

    return count;
}

void Game::SetCell(Matrix2D<CellState>* mat, int32_t x, int32_t y, CellState value)
{
    (*mat)[y][x] = value;
}
