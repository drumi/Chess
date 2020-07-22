#include "MoveValidator.h"
#include <cassert>

bool MoveValidator::isValid(Board const& board, int x, int y, int xdest, int ydest, int xEnpassant)
{
    Piece const** pieces = board.getPieces();
    Piece piece = pieces[y][x];

    if(x > 8 || y > 8 || x < 0 || y < 0 || xdest > 8 || ydest > 8 || xdest < 0 || ydest < 0 || (x == xdest && y == ydest))
        return false;
    if(pieces[y][x].getType() == pieces[ydest][xdest].getType())
        return false;    
    switch (piece.getType())
    {
        case PieceType::EMPTY:
            return false;
            break;
        case PieceType::PAWN:
            if(piece.isWhite())
            {
                
            }
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

    return true;
}