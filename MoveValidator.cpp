#include "MoveValidator.h"
#include <cassert>
#include <iostream>
#include <functional>

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
            if(x != xdest && y != ydest && xdest - ydest != x - y && xdest + ydest != x + y) // Check if we move like bishop or rook
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
        case PieceType::KING:
            if(abs(y - ydest) > 1 || abs(x - xdest) > 2) // Check if we move more than allowed
                return false;
            else if(abs(x - xdest) == 2) // Trying castling
            {
                if(piece.hasMoved())
                    return false;
                if(xdest > x)
                {
                    if((*pieces)[ydest][7].hasMoved())
                        return false;
                    if(((*pieces)[y][x + 1].getType() != PieceType::EMPTY) || ((*pieces)[y][x + 2].getType() != PieceType::EMPTY))
                        return false;
                    if(isSquareUnderAttack(board, x, y, !piece.isWhite()) ||isSquareUnderAttack(board, x + 1, y, !piece.isWhite()) || isSquareUnderAttack(board, x + 2, y, !piece.isWhite()))
                        return false;
                }
                else
                {
                    if((*pieces)[ydest][0].hasMoved())
                        return false;
                    if(((*pieces)[y][x - 1].getType() != PieceType::EMPTY) || ((*pieces)[y][x - 2].getType() != PieceType::EMPTY || ((*pieces)[y][x - 3].getType() != PieceType::EMPTY)))
                        return false;
                    if(isSquareUnderAttack(board, x, y, !piece.isWhite()) || isSquareUnderAttack(board, x - 1, y, !piece.isWhite()) || isSquareUnderAttack(board, x - 2, y, !piece.isWhite()) || isSquareUnderAttack(board, x - 3, y, !piece.isWhite()))
                        return false;
                }
            }
            break;
        default:
            assert(false);
            break;
    }
    return !isKingUnderCheck(board, !piece.isWhite());
}

bool MoveValidator::isSquareUnderAttack(Board const& board, int x, int y, bool fromWhite)
{
    boardArrPtr pieces = board.getPieces();

    // Check for attacks from knights
    bool isUnderAttack = false;
    for(int i = -1; i <= 1; i += 2)
        for(int j = -2; j <= 2; j += 4)
        {
            if(y + i >= 0 && y + i < 8 && x + j >= 0 && x + j < 8)
                isUnderAttack |= (*pieces)[y + i][x + j].getType() == PieceType::KNIGHT && 
                                 (*pieces)[y + i][x + j].isWhite() == fromWhite;
            
            if(y + j >= 0 && y + j < 8 && x + i >= 0 && x + i < 8)
                isUnderAttack |= (*pieces)[y + j][x + i].getType() == PieceType::KNIGHT && 
                                 (*pieces)[y + j][x + i].isWhite() == fromWhite;
        }
        
    if(isUnderAttack)
        return true;

    // Check for attack horizontally up
    for(int i = x + 1; i < 8; ++i)
    {
        Piece piece = (*pieces)[y][i];
        if(piece.getType() != PieceType::EMPTY)
        {
            if(piece.isWhite() != fromWhite) // We are blocked from a figure of same color
                break;
            else
            {
                if(piece.getType() == PieceType::KING && abs(i - x) == 1) // Attacked by king
                    return true;
                else if(piece.getType() == PieceType::ROOK || piece.getType() == PieceType::QUEEN) // Attacked by Queen/rook
                    return true;
                else
                    break; // Blocked by figure from other color that cannot attack us
            }
            
        }
    }

    // Check for attack horizontally down
    for(int i = x - 1; i >= 0; --i)
    {
        Piece piece = (*pieces)[y][i];
        if(piece.getType() != PieceType::EMPTY)
        {
            if(piece.isWhite() != fromWhite) // We are blocked from a figure of same color
                break;
            else
            {
                if(piece.getType() == PieceType::KING && abs(i - x) == 1) // Attacked by king
                    return true;
                else if(piece.getType() == PieceType::ROOK || piece.getType() == PieceType::QUEEN) // Attacked by Queen/rook
                    return true;
                else
                    break; // Blocked by figure from other color that cannot attack us
            }
            
        }
    }

    // Check for attack vertically down
    for(int i = y - 1; i >= 0; --i)
    {
        Piece piece = (*pieces)[x][i];
        if(piece.getType() != PieceType::EMPTY)
        {
            if(piece.isWhite() != fromWhite) // We are blocked from a figure of same color
                break;
            else
            {
                if(piece.getType() == PieceType::KING && abs(i - y) == 1) // Attacked by king
                    return true;
                else if(piece.getType() == PieceType::ROOK || piece.getType() == PieceType::QUEEN) // Attacked by Queen/rook
                    return true;
                else
                    break; // Blocked by figure from other color that cannot attack us
            }
            
        }
    }

    // Check for attack vertically up
    for(int i = y + 1; i < 8; ++i)
    {
        Piece piece = (*pieces)[x][i];
        if(piece.getType() != PieceType::EMPTY)
        {
            if(piece.isWhite() != fromWhite) // We are blocked from a figure of same color
                break;
            else
            {
                if(piece.getType() == PieceType::KING && abs(i - y) == 1) // Attacked by king
                    return true;
                else if(piece.getType() == PieceType::ROOK || piece.getType() == PieceType::QUEEN) // Attacked by Queen/rook
                    return true;
                else
                    break; // Blocked by figure from other color that cannot attack us
            }
            
        }
    }

    return false;
}


bool MoveValidator::isKingUnderCheck(Board const& board, bool isWhite)
{
    return false;
}
