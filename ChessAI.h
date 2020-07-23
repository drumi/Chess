#pragma once
#include "MoveGenerator.h"

class ChessAI
{
    private:
        ChessAI(){}
    public:
        static MoveResult GetMove(Board const& board, bool isWhiteTurn, int depth);
};