#include "MoveValidator.h"
#include <cassert>

bool MoveValidator::isValid(Board const& board, int x, int y, int xdest, int ydest, int xEnpassant)
{
    boardArrPtr pieces = board.getPieces();

    if(x > 8 || y > 8 || x < 0 || y < 0 || xdest > 8 || ydest > 8 || xdest < 0 || ydest < 0 || (x == xdest && y == ydest))
        return false;
    if((*pieces)[y][x].isWhite() == (*pieces)[ydest][xdest].isWhite() && (*pieces)[ydest][xdest].getType() != PieceType::EMPTY)
        return false;    

    Piece piece = (*pieces)[y][x];

    switch (piece.getType())
    {
        case PieceType::EMPTY:
            return false;
            break;
        case PieceType::PAWN:
            if(ydest - y >= 0 && piece.isWhite() || ydest - y <= 0 && !piece.isWhite())
                return false;
            else if(x == xdest && (*pieces)[ydest][xdest].getType() != PieceType::EMPTY)
                return false;
            else if(abs(x - xdest) > 1 || abs(y - ydest) > 2 || (abs(y - ydest) > 1 && piece.hasMoved()))
                return false;
            else if(abs(x - xdest) == 1)
            {
                if((*pieces)[ydest][xdest].getType() == PieceType::EMPTY)
                {
                    if(xdest != xEnpassant)
                        return false;
                    else if(piece.isWhite() && ydest != 1 || !piece.isWhite() && ydest != 6)
                        return false;
                }      
                else if((*pieces)[ydest][xdest].isWhite() == piece.isWhite())
                    return false;
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

static bool isKingUnderCheck(Board const& board, bool isWhite)
{
    return false;
}
