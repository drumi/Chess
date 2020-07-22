#include "Board.h"
#include <cassert>

Board::Board()
{
    init();
}

Board::Board(boardArrPtr _board)
{
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            m_board[i][j] = (*_board)[i][j];
        }
        
    }
    
}

Board::Board(Board const& _board)
{
    Board(_board.getPieces());
}


void Board::init()
{
    for (size_t i = 0; i < 8; i++)
    {
        m_board[1][i] = Piece(false, PieceType::PAWN);
        m_board[6][i] = Piece(true, PieceType::PAWN);
    }

    m_board[0][0] = Piece(false, PieceType::ROOK);
    m_board[0][1] = Piece(false, PieceType::KNIGHT);
    m_board[0][2] = Piece(false, PieceType::BISHOP);
    m_board[0][3] = Piece(false, PieceType::QUEEN);
    m_board[0][4] = Piece(false, PieceType::KING);
    m_board[0][5] = Piece(false, PieceType::BISHOP);
    m_board[0][6] = Piece(false, PieceType::KNIGHT);
    m_board[0][7] = Piece(false, PieceType::ROOK);

    m_board[7][0] = Piece(true, PieceType::ROOK);
    m_board[7][1] = Piece(true, PieceType::KNIGHT);
    m_board[7][2] = Piece(true, PieceType::BISHOP);
    m_board[7][3] = Piece(true, PieceType::QUEEN);
    m_board[7][4] = Piece(true, PieceType::KING);
    m_board[7][5] = Piece(true, PieceType::BISHOP);
    m_board[7][6] = Piece(true, PieceType::KNIGHT);
    m_board[7][7] = Piece(true, PieceType::ROOK);
}

void Board::move(int x, int y, int xdest, int ydest)
{
    assert(x < 8 && y < 8 && xdest < 8 && ydest < 8 && x >=0 && y >= 0 && xdest >= 0 && ydest >= 0);

    m_board[y][x].setMoved();
    m_board[ydest][xdest] = m_board[y][x];
}