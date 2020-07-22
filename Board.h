#pragma once

#include "Piece.h"
#include <vector>

class Board
{
    private:
    Piece m_board[8][8];
    void init();

    public:
    Board();
    Board(Piece const** _board);
    Board(Board const& _board);
    void move(int x, int y, int xdest, int ydest); //TODO push on stack history
    Piece const** getPieces() const { return (Piece const**)m_board; }
};