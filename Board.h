#pragma once

#include "Piece.h"
#include <vector>

typedef Piece const (*boardArrPtr)[8][8];

class Board
{
    private:
    Piece m_board[8][8];
    void init();

    public:
    Board();
    Board(boardArrPtr _board);
    Board(Board const& _board);
    void move(int x, int y, int xdest, int ydest); //TODO push on stack history
    boardArrPtr getPieces() const { return &m_board; }
};