#include "MoveValidator.h"
#include <cassert>
#include <iostream>
#include <functional>

bool MoveValidator::isValid(Board const& board, int x, int y, int xdest, int ydest, int xEnpassant)
{
    boardArrPtr pieces = board.getPieces();
    // Check if coordinates are out of bounds or they are the same
    if(x >= 8 || y >= 8 || x < 0 || y < 0 || xdest >= 8 || ydest >= 8 || xdest < 0 || ydest < 0 || (x == xdest && y == ydest))
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
            if(abs(ydest - y) == 2)
                if(ydest > y && (*pieces)[ydest - 1][x].getType() != PieceType::EMPTY)
                    return false;
                else if(ydest < y && (*pieces)[ydest + 1][x].getType() != PieceType::EMPTY)
                    return false;
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
                    else if(piece.isWhite() && ydest != 2 || !piece.isWhite() && ydest != 5)
                        return false;
                    else
                    {
                        if(piece.isWhite() && isKingUnderCheck(Board(board).remove(xdest, 3), true))
                            return false;
                        else if(!piece.isWhite() && isKingUnderCheck(Board(board).remove(xdest, 4), false))
                            return false;
                    }
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
                for(int i = std::min(x, xdest) + 1; i < std::max(x, xdest); ++i)
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
                int minx = std::min(xdest, x);
                int miny = std::min(ydest, y);
                
                int maxx = std::max(xdest, x);
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
                    for(int i = std::min(x, xdest) + 1; i < std::max(x, xdest); ++i)
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
                    if(isSquareUnderAttack(board, x, y, !piece.isWhite()) || isSquareUnderAttack(board, x - 1, y, !piece.isWhite()) || isSquareUnderAttack(board, x - 2, y, !piece.isWhite()))
                        return false;
                }
            }
            break;
        default:
            assert(false);
            break;
    }

    return !isKingUnderCheck(Board(board).move(x, y, xdest, ydest), piece.isWhite());
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

    // Check if under attack from king or pawn
    for(int i = x-1; i <= x + 1; ++i)
        for(int j = y-1; j <= y + 1; ++j)
        {
            if(i < 8 && j < 8 && i >=0 && j >=0 )
            {
                if((*pieces)[j][i].getType() == PieceType::KING && (*pieces)[j][i].isWhite() == fromWhite)
                    return true;
                if((*pieces)[j][i].getType() == PieceType::PAWN && (*pieces)[j][i].isWhite() == fromWhite)
                    if(fromWhite && i != x && j - y > 0)
                        return true;
                    else if(!fromWhite && i != x && j - y < 0)
                        return true;
            }
        }

    std::pair<int, int> initValue[] = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}, {x + 1, y + 1}, { x + 1, y - 1}, {x - 1, y - 1}, {x - 1, y + 1}};
    std::function<void(int&, int&)> next[]  = {[](int& a, int& b){ ++a; }, [](int& a, int& b){ --a; }, [](int& a, int& b){ ++b; }, [](int& a, int& b){ --b; }, [](int& a, int& b){ ++a; ++b; }, [](int& a, int& b){ ++a; --b; }, [](int& a, int& b){ --a; --b; }, [](int& a, int& b){ --a; ++b; }};
    std::function<bool(int, int)> check[] = {[](int a, int b) { return a < 8;}, [](int a, int b) { return a >= 0;}, [](int a, int b) { return b < 8;}, [](int a, int b) { return b >= 0;}, [](int a, int b) { return a < 8 && b < 8;}, [](int a, int b) { return a < 8 && b >= 0;}, [](int a, int b) { return a >= 0 && b >= 0;}, [](int a, int b) { return a >= 0 && b < 8;}};
    
    for(int i, j, k=0; k < 8; ++k)
    {
        for(i = initValue[k].first, j = initValue[k].second; check[k](i, j); next[k](i, j))
        {
            Piece piece = (*pieces)[j][i];
            if(piece.getType() != PieceType::EMPTY)
            {
                if(piece.isWhite() != fromWhite) // We are blocked by a figure of the same color
                    break;
                else
                {
                    if(piece.getType() == PieceType::QUEEN)
                        return true;
                    else if(piece.getType() == PieceType::ROOK && k < 4)
                        return true;
                    else if(piece.getType() == PieceType::BISHOP &&  k >= 4)
                        return true;
                    else
                        break; // Blocked by figure from other color that cannot attack us
                }   
            }
        }
    }
    return false;
}


bool MoveValidator::isKingUnderCheck(Board const& board, bool isWhite)
{
    boardArrPtr pieces = board.getPieces();

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            if((*pieces)[y][x].getType() == PieceType::KING && (*pieces)[y][x].isWhite() == isWhite)
                return isSquareUnderAttack(board, x, y, !isWhite);
        }
        
    }
    assert(false);
    return false;
}
