#include "MoveGenerator.h"
#include "MoveValidator.h"
#include <cassert>

std::vector<Board> MoveGenerator::Generate(Board const& board, bool generateForWhite, int xEnpassant)
{
    boardArrPtr pieces = board.getPieces();
    std::vector<Board> result;

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if((*pieces)[y][x].getType() == PieceType::EMPTY || (*pieces)[y][x].isWhite() != generateForWhite)
                continue;

            switch ((*pieces)[y][x].getType()) // Guaranteed to be for the color for generation
            {
            case PieceType::PAWN:
                if(generateForWhite)
                {
                    if(MoveValidator::isValid(board, x, y, x, y - 2))
                        result.push_back(Board(board).move(x, y, x, y - 2));
                    for (int i = -1; i <= 1; i++)
                    {
                        if(MoveValidator::isValid(board, x, y, x + i, y - 1, xEnpassant))
                            if(x + i == xEnpassant && y == 2)
                                result.push_back(Board(board).move(x, y, x + i, y - 1).remove(xEnpassant, 3));
                            else if(y == 0)
                                result.push_back(Board(board).move(x, y, x + i, y - 1).setPieceType(x + i, 0, PieceType::QUEEN));
                            else
                                result.push_back(Board(board).move(x, y, x + i, y - 1));
                    }
                    
                }
                else
                {
                    if(MoveValidator::isValid(board, x, y, x, y + 2))
                        result.push_back(Board(board).move(x, y, x, y + 2));
                    for (int i = -1; i <= 1; i++)
                    {
                        if(MoveValidator::isValid(board, x, y, x + i, y + 1, xEnpassant))
                            if(x + i == xEnpassant && y == 5)
                                result.push_back(Board(board).move(x, y, x + i, y + 1).remove(xEnpassant, 4));
                            else if(y == 7)
                                result.push_back(Board(board).move(x, y, x + i, y + 1).setPieceType(x + i, 0, PieceType::QUEEN));
                            else
                                result.push_back(Board(board).move(x, y, x + i, y + 1));
                    }
                }
                
                break;
            case PieceType::ROOK:
                for (int i = 0; i < 8; ++i)
                {
                    if(MoveValidator::isValid(board, x, y, i, y))
                        result.push_back(Board(board).move(x, y, i, y));
                    if(MoveValidator::isValid(board, x, y, x, i))
                        result.push_back(Board(board).move(x, y, x, i));
                }   
                break;
            case PieceType::KNIGHT:
                for(int i = -1; i <= 1; i += 2)
                    for(int j = -2; j <= 2; j += 4)
                    {
                        if(MoveValidator::isValid(board, x, y, x + j, y + i))
                            result.push_back(Board(board).move(x, y, x + j, y + i));
                        if(MoveValidator::isValid(board, x, y, x + i, y + j))
                            result.push_back(Board(board).move(x, y, x + i, y + j));
                    }
                break;
            case PieceType::BISHOP:
                for (int i = 0; i < 8; i++)
                {
                    if(MoveValidator::isValid(board, x, y, x + i, y + i))
                        result.push_back(Board(board).move(x, y, x + i, y + i));
                    if(MoveValidator::isValid(board, x, y, x + i, y - i))
                        result.push_back(Board(board).move(x, y, x + i, y - i));
                    if(MoveValidator::isValid(board, x, y, x - i, y + i))
                        result.push_back(Board(board).move(x, y, x - i, y + i));
                    if(MoveValidator::isValid(board, x, y, x - i, y - i))
                        result.push_back(Board(board).move(x, y, x - i, y - i));
                }
                break;
            case PieceType::QUEEN:
                for (int i = 0; i < 8; i++)
                {
                    if(MoveValidator::isValid(board, x, y, x + i, y + i))
                        result.push_back(Board(board).move(x, y, x + i, y + i));
                    if(MoveValidator::isValid(board, x, y, x + i, y - i))
                        result.push_back(Board(board).move(x, y, x + i, y - i));
                    if(MoveValidator::isValid(board, x, y, x - i, y + i))
                        result.push_back(Board(board).move(x, y, x - i, y + i));
                    if(MoveValidator::isValid(board, x, y, x - i, y - i))
                        result.push_back(Board(board).move(x, y, x - i, y - i));
                }
                for (int i = 0; i < 8; ++i)
                {
                    if(MoveValidator::isValid(board, x, y, i, y))
                        result.push_back(Board(board).move(x, y, i, y));
                    if(MoveValidator::isValid(board, x, y, x, i))
                        result.push_back(Board(board).move(x, y, x, i));
                }
                break;
            case PieceType::KING:
                if(MoveValidator::isValid(board, x, y, x-2, y))
                    result.push_back(Board(board).move(x, y, x-2, y).move(0, y, 3, y));
                if(MoveValidator::isValid(board, x, y, x+2, y))
                    result.push_back(Board(board).move(x, y, x+2, y).move(7, y, 5, y));

                for(int i = x-1; i <= x + 1; ++i)
                    for(int j = y-1; j <= y + 1; ++j)
                        if(MoveValidator::isValid(board, x, y, i, j))
                            result.push_back(Board(board).move(x, y, i, j));
                break;
            default:
                assert(false);
                break;
            }
        }
    }
    return result;
}