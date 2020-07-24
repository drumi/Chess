#include "ChessAI.h"

#include <stdlib.h>
#include <time.h> 

int minimax(Board const& board, bool isWhiteTurn, int depth, int a = INT_MIN, int b = INT_MAX)
{
    if(depth == 0)
        return board.getScore();

    std::vector<MoveResult> moves = MoveGenerator::Generate(board, isWhiteTurn);

    if(moves.size() == 0)
        return isWhiteTurn? INT_MIN : INT_MAX;

    int value;

    if(isWhiteTurn)
    {
        value = INT_MIN;
        for(auto& move : moves)
        {
            value = std::max(value, minimax(move.board, false, depth - 1, a, b));
            a = std::max(a, value);
            if (a >= b)
                break;
        }
    }
    else
    {
        value = INT_MAX;
        for(auto& move : moves)
        {
            value = std::min(value, minimax(move.board, true, depth - 1));
            b = std::min(b, value);
            if (b <= a)
                break;
        }
    }
    return value;
}

MoveResult ChessAI::GetMove(Board const& board, bool isWhiteTurn, int depth)
{  
    std::vector<MoveResult> moves = MoveGenerator::Generate(board, isWhiteTurn);
    int bestIndex = 0, bestValue;
    if(isWhiteTurn)
    {
        bestValue = INT_MIN;
        for(int i = 0; i < moves.size(); ++i)
        {
            int tmp = minimax(moves[i].board, false, depth - 1);
            if(tmp > bestValue)
            {
                bestValue = tmp;
                bestIndex = i;
            } 
        }
    }
    else
    {
        bestValue = INT_MAX;
        for(int i = 0; i < moves.size(); ++i)
        {
            int tmp = minimax(moves[i].board, true, depth - 1);
            if(tmp < bestValue)
            {
                bestValue = tmp;
                bestIndex = i;
            } 
        }
        std::cout << bestValue << std::endl;
    }
    
    return moves[bestIndex];
}
