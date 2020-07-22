#include "MoveValidator.h"
#include <cassert>
#include <iostream>

bool MoveValidator::isValid(Board const& board, int x, int y, int xdest, int ydest, int xEnpassant)
{
    boardArrPtr pieces = board.getPieces();

    // Check if coordinates are out of bounds or they are the same
    if(x > 8 || y > 8 || x < 0 || y < 0 || xdest > 8 || ydest > 8 || xdest < 0 || ydest < 0 || (x == xdest && y == ydest))
        return false;
    // Check if we go on piece with same color
    if((*pieces)[y][x].isWhite() == (*pieces)[ydest][xdest].isWhite() && (*pieces)[ydest][xdest].getType() != PieceType::EMPTY)
        return false;    

    Piece piece = (*pieces)[y][x];
    // Check if move is valid for piece (does not check illegal moves for exposing king)
    switch (piece.getType())
    {
        case PieceType::EMPTY:
            return false;
            break;
        case PieceType::PAWN:
            if(ydest - y >= 0 && piece.isWhite() || ydest - y <= 0 && !piece.isWhite()) // Check if pawn moves in the right direction
                return false;
            else if(x == xdest && (*pieces)[ydest][xdest].getType() != PieceType::EMPTY) // Check if when pawn moves forward there are no figures blocking
                return false;
            else if(abs(x - xdest) > 1 || abs(y - ydest) > 2 || (abs(y - ydest) > 1 && piece.hasMoved())) // Check if pawn moves more than 2 (or 1 with first move) squares
                return false;
            else if(abs(x - xdest) == 1)
            {
                if(abs(y - ydest) == 2) // Check if we have tried taking piece on first move by moving 2 squares
                    return false;
                else if((*pieces)[ydest][xdest].getType() == PieceType::EMPTY)
                {
                    if(xdest != xEnpassant) // Check en passant rule
                        return false;
                    else if(piece.isWhite() && ydest != 1 || !piece.isWhite() && ydest != 6)
                        return false;
                } 
            }
            break;
        case PieceType::ROOK:
            if(x != xdest && y != ydest) // Check if we move horizontally or vertically
                return false;
            else if(x == xdest) 
            {
                // Check if there are no figures between
                for(int i = std::min(y, ydest) + 1; i < std::max(y, ydest); ++i)
                    if((*pieces)[i][x].getType() != PieceType::EMPTY)
                        return false;
            }
            else if(y == ydest) 
            {
                // Check if there are no figures between
                for(int i = std::min(x, xdest) + 1; i < std::max(x, xdest) - 1; ++i)
                    if((*pieces)[y][i].getType() != PieceType::EMPTY)
                        return false;
            }
            break;
        case PieceType::KNIGHT:
            // Check G move 
            if(!(abs(x - xdest) == 1 && abs(y - ydest) == 2 || abs(x - xdest) == 2 && abs(y - ydest) == 1))
                return false;
            break;
        case PieceType::BISHOP:
            if(xdest - ydest != x - y && xdest + ydest != x + y)
                return false;
            else if(xdest - ydest == x - y)
            {
                int minx = std::min(xdest,x);
                int miny = std::min(ydest, y);
                
                int maxx = std::max(xdest,x);
                int maxy = std::max(ydest, y);

                ++minx;
                ++miny;
                while(minx != maxx)
                {
                    if((*pieces)[miny][minx].getType() != PieceType::EMPTY)
                        return false;
                    ++minx;
                    ++miny;
                }
            }
            else if(xdest + ydest == x + y)
            {
                int minx = std::min(xdest,x);
                int miny = std::min(ydest, y);
                
                int maxx = std::max(xdest,x);
                int maxy = std::max(ydest, y);

                ++minx;
                --maxy;
                while(minx != maxx)
                {
                    if((*pieces)[maxy][minx].getType() != PieceType::EMPTY)
                        return false;
                    ++minx;
                    --maxy;
                }
            }
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
