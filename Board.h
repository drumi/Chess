#pragma once
#include "Piece.h"
#include <vector>

class Board
{
    private:
    std::vector<Piece*> pieces;
    void init();

    public:
    Board();
};