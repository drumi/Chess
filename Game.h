#pragma once

#include "Board.h"
#include "MoveGenerator.h"
#include "MoveValidator.h"
#include <stack>


class Game
{
    private:
    struct Tuple
    {
        PieceType pieceType;
        int x, y, xdest, ydest;
    };

    bool m_isWhiteTurn;
    Board m_board;
    std::stack<Board> m_boardHistory;
    std::stack<Tuple> m_pieceHistory;


    public:
    Game();
    bool tryMove(int x, int y, int xdest, int ydest);
    bool isWhiteTurn() const { return m_isWhiteTurn; }
    void undoMove();
    Board getBoard() const { return m_board;}

};