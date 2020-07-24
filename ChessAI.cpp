#include "ChessAI.h"

namespace
{
    int pawn_weight[] = { 
        #include "Weights/pawn.txt" 
        };

    int bishop_weight[] = { 
        #include "Weights/bishop.txt" 
        };

    int knight_weight[] = { 
        #include "Weights/knight.txt" 
        };

    int rook_weight[] = { 
        #include "Weights/rook.txt" 
        };

    int queen_weight[] = { 
        #include "Weights/queen.txt" 
        };

    int king_weight[] = { 
        #include "Weights/king.txt" 
        };
}

int ChessAI::calulateScore(Board const& board)
{
    int score = 0;
    boardArrPtr pieces = board.getPieces();
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Piece p = (*pieces)[y][x];

            switch (p.getType())
            {
            case PieceType::PAWN:
                score += p.isWhite() ? (100 + pawn_weight[8 * y + x]) : (-100 - pawn_weight[8 * (7 - y) + x]);
                break;

            case PieceType::KNIGHT:
                score += p.isWhite() ? (320 + knight_weight[8 * y + x]) : (-320 - knight_weight[8 * (7 - y) + x]);
                break;

            case PieceType::BISHOP:
                score += p.isWhite() ? (330 + bishop_weight[8 * y + x]) : (-330 - bishop_weight[8 * (7 - y) + x]);
                break;

            case PieceType::ROOK:
                score += p.isWhite() ? (500 + rook_weight[8 * y + x]) : (-500 - rook_weight[8 * (7 - y) + x]);
                break;

            case PieceType::QUEEN:
                score += p.isWhite() ? (900 + queen_weight[8 * y + x]) : (-900 - queen_weight[8 * (7 - y) + x]);
                break;

            case PieceType::KING:
                score += p.isWhite() ? (20000 + king_weight[8 * y + x]) : (-20000 - king_weight[8 * (7 - y) + x]);
                break;
            }
        }
    }
    
    return score;
}
int ChessAI::minimax(Board const& board, bool isWhiteTurn, int depth, int a, int b)
{
    if(depth == 0)
        return calulateScore(board);

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
            value = std::min(value, minimax(move.board, true, depth - 1, a, b));
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
    }

    std::cout << bestValue << std::endl;
    return moves[bestIndex];
}
