#include "ChessAI.h"

#include <stdlib.h>
#include <time.h> 

MoveResult ChessAI::GetMove(Board const& board, bool isWhiteTurn, int depth)
{
    srand (time(NULL));
    std::vector<MoveResult> r = MoveGenerator::Generate(board, isWhiteTurn);
    return r[rand() % r.size()];
}