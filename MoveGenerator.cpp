#include "MoveGenerator.h"
#include <cassert>

std::vector<Board> MoveGenerator::Generate(Board const& board, bool generateForWhite, int xEnpassant)
{
    Piece const** pieces = board.getPieces();

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            switch (pieces[i][j].getType())
            {
            case PieceType::EMPTY:
                continue;
                break;
            case PieceType::PAWN:
                break;
            case PieceType::ROOK:
                break;
            case PieceType::KNIGHT:
                break;
            case PieceType::BISHOP:
                break;
            case PieceType::QUEEN:
                break;
            case PieceType::KING:
                break;
            default:
                assert(false);
                break;
            }
        }
    }
    return std::vector<Board>();
}