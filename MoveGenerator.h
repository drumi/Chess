#pragma once

#include "Board.h"

struct MoveResult
{
    Board board;
    int x;
    int y;
    int xdest;
    int ydest;
};

class MoveGenerator
{
    private:
    MoveGenerator(){};
    public:
    static std::vector<MoveResult> Generate(Board const& board, bool generateForWhite = true, int xEnpassant = -999);
};