#pragma once

#include "Board.h"

class MoveGenerator
{
    private:
    MoveGenerator(){};
    public:
    static std::vector<Board> Generate(Board const& board, bool generateForWhite = true, int xEnpassant = -1);
};