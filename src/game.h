#pragma once

#include "common.h"
#include "matrix.h"

enum CellState : bool
{
    ALIVE = true,
    DEAD = false
};

class Game
{
public:
    const int32_t GridWidth;
    const int32_t GridHeigth;

public:
    Game(int32_t grid_width, int32_t grid_heigth);

    CellState GetCellState(int32_t x, int32_t y);
    void RandomGame();
    void Next();

private:
    int32_t CountAliveNeighbors(int32_t x, int32_t y);
    void SetCell(Matrix2D<CellState>* grid, int32_t x, int32_t y, CellState value);

private:
    Matrix2D<CellState> m_FrontGrid;
    Matrix2D<CellState> m_BackGrid;

    Matrix2D<CellState>* m_CurrentGrid;
    Matrix2D<CellState>* m_OtherGrid;
};
