#pragma once

#include "common.h"
#include "matrix.h"

enum CellState : char8_t
{
    ALIVE = 0,
    DEAD
};

enum GameState
{
    RUN = 0,
    PAUSE,
    STOP
};

class Game
{
public:
    const int32_t GridWidth;
    const int32_t GridHeight;

public:
    Game(int32_t grid_width, int32_t grid_height);

    CellState GetCellState(int32_t x, int32_t y);
    void RandomGame();
    GameState GetState();
    void SetState(GameState state);
    void Update();

private:
    int32_t CountAliveNeighbors(int32_t x, int32_t y);
    void SetCell(Matrix2D<CellState>* grid, int32_t x, int32_t y, CellState value);

private:
    GameState m_State;

    Matrix2D<CellState> m_FrontGrid;
    Matrix2D<CellState> m_BackGrid;

    Matrix2D<CellState>* m_CurrentGrid;
    Matrix2D<CellState>* m_OtherGrid;
};
