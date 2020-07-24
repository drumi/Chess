#pragma once
#include "MoveGenerator.h"

class ChessAI
{
    private:
        ChessAI(){}
        static int calulateScore(Board const& board);
        static int minimax(Board const& board, bool isWhiteTurn, int depth, int a = INT_MIN, int b = INT_MAX);
    public:
        static MoveResult GetMove(Board const& board, bool isWhiteTurn, int depth);
};