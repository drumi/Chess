#pragma once
#include "Board.h"

class MoveValidator
{
private:
    MoveValidator(){}
public:
    static bool isValid(Board const& board, int x, int y, int xdest, int ydest, int xEnpassant = -1);
    static bool isKingUnderCheck(Board const& board, bool isWhite);
    static bool isSquareUnderAttack(Board const& board, int x, int y, bool fromWhite);
};

