#include "MoveGenerator.h"
#include "MoveValidator.h"
#include <cassert>

std::vector<Board> MoveGenerator::Generate(Board const& board, bool generateForWhite, int xEnpassant)
{
    boardArrPtr pieces = board.getPieces();
    std::vector<Board> result;

    for (size_t x = 0; x < 8; x++)
    {
        for (size_t y = 0; y < 8; y++)
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
                    for (size_t i = -1; i <= 1; i++)
                    {
                        if(MoveValidator::isValid(board, x, y, x + i, y - 1, xEnpassant))
                            result.push_back(Board(board).move(x, y, x + i, y - 1));
                    }
                    
                }
                else
                {
                    if(MoveValidator::isValid(board, x, y, x, y + 2))
                        result.push_back(Board(board).move(x, y, x, y + 2));
                    for (size_t i = -1; i <= 1; i++)
                    {
                        if(MoveValidator::isValid(board, x, y, x + i, y + 1, xEnpassant))
                            result.push_back(Board(board).move(x, y, x + i, y + 1));
                    }
                }
                
                break;
            case PieceType::ROOK:
                for (size_t i = 0; i < 8; ++i)
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
                for (size_t i = x; i < 8; i++)
                {
                    for (size_t j = y; j < 8; j++)
                    {
                        /* code */
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
        }
    }
    return result;
}