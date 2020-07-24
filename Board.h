#pragma once

#include "Piece.h"
#include <vector>
#include <iostream>

typedef Piece const (*boardArrPtr)[8][8];

class Board
{
    private:
    Piece m_board[8][8];
    int m_score;
    void init();
    void recalculateScore(Piece p, bool remove);

    public:
    Board();
    Board(boardArrPtr _board);
    Board(Board const& _board);
    Board& move(int x, int y, int xdest, int ydest);
    boardArrPtr getPieces() const { return &m_board; }
    Board& setPieceType(int x, int y, PieceType pt);
    Piece getPiece(int x, int y) const { return m_board[y][x]; }
    Board& remove(int x, int y);
    bool operator == (Board const& other) const;
    int getScore() const { return m_score; }
};

std::ostream& operator << (std::ostream& out, Board const& board);