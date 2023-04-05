#include "game.h"
#include "common.h"

Game::Game(int32_t grid_width, int32_t grid_heigth) :
    GridWidth(grid_width), GridHeigth(grid_heigth),
    m_FrontGrid(grid_width, grid_heigth),
    m_BackGrid(grid_width, grid_heigth)
{
    m_CurrentGrid = &m_FrontGrid;
    m_OtherGrid = &m_BackGrid;
}

CellState Game::GetCellState(int32_t x, int32_t y)
{
    if (x > GridWidth - 1)
        x -= GridWidth;
    else if (x < 0)
        x = GridWidth + x;

    if (y > GridHeigth - 1)
        y -= GridHeigth;
    else if (y < 0)
        y = GridHeigth + y;

    return (*m_CurrentGrid)[y][x];
}

void Game::RandomGame()
{
    std::srand((uint32_t)std::time(NULL));

    // TODO: create a funtion to copy a Matrix2D
    for (int32_t y = 0; y < GridHeigth; ++y) {
        for (int32_t x = 0; x < GridWidth; ++x) {
            CellState result = (std::rand() % 2) ? CellState::ALIVE : CellState::DEAD;
            SetCell(m_CurrentGrid, y, x, result);
            SetCell(m_OtherGrid, y, x, result);
        }
    }
}

void Game::Next()
{
    for (int32_t y = 0; y < GridHeigth; ++y) {
        for (int32_t x = 0; x < GridWidth; ++x) {
            int32_t neighbors = CountAliveNeighbors(x, y);
            CellState cell_state = GetCellState(x, y);

            if (cell_state == CellState::ALIVE && (neighbors < 2 || neighbors > 3)) {
                SetCell(m_OtherGrid, x, y, CellState::DEAD);
            }
            else if (cell_state == CellState::ALIVE && (neighbors == 3 || neighbors == 2)) {
                SetCell(m_OtherGrid, x, y, CellState::ALIVE);
            }
            else if (cell_state == CellState::DEAD && neighbors == 3) {
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
