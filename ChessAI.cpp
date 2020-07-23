#include "ChessAI.h"

MoveResult ChessAI::GetMove(Board const& board, bool isWhiteTurn, int depth)
{
    return MoveGenerator::Generate(board, isWhiteTurn)[0];
}