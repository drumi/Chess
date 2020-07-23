#pragma once

#include "Piece.h"
#include <vector>
#include <iostream>

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
    Board& move(int x, int y, int xdest, int ydest);
    boardArrPtr getPieces() const { return &m_board; }
    Board& setPieceType(int x, int y, PieceType pt) { m_board[y][x].setType(pt); return *this;}
    Piece getPiece(int x, int y) const { return m_board[y][x]; }
    Board& remove(int x, int y) { m_board[y][x].setType(PieceType::EMPTY); return *this;};
    bool operator == (Board const& other) const;
};

std::ostream& operator << (std::ostream& out, Board const& board);