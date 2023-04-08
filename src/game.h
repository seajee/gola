#pragma once

#include "common.h"
#include "matrix.h"
#include "cell.h"

typedef Matrix2D<CellState> CellGrid;

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

    GameState GetState();
    void SetState(GameState state);

    CellState GetCell(int32_t x, int32_t y);
    bool CellChanged(int32_t x, int32_t y);

    void RandomGame();
    void Update();

private:
    int32_t CountNeighbors(int32_t x, int32_t y);

    CellState GetCell(CellGrid* grid, int32_t x, int32_t y);
    void SetCell(CellGrid* grid, int32_t x, int32_t y, CellState state);

private:
    GameState m_State;

    CellGrid m_FrontGrid;
    CellGrid m_BackGrid;

    CellGrid* m_CurrentGrid;
    CellGrid* m_OtherGrid;
};
