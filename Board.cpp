#include "Board.h"
#include <iostream>
#include <cassert>

Board::Board()
:m_score(0)
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
:Board(_board.getPieces())
{
    m_score = _board.m_score;
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

void Board::recalculateScore(Piece p, bool remove)
{
    switch (p.getType())
    {
    case PieceType::PAWN:
        m_score += p.isWhite() ^ remove ? 1 : -1;
        break;

    case PieceType::KNIGHT:
    case PieceType::BISHOP:
        m_score += p.isWhite() ^ remove ? 3 : -3;
        break;

    case PieceType::ROOK:
        m_score += p.isWhite() ^ remove ? 5 : -5;
        break;

    case PieceType::QUEEN:
        m_score += p.isWhite() ^ remove ? 9 : -9;
        break;
    }
}

Board& Board::setPieceType(int x, int y, PieceType pt) 
{ 
    recalculateScore(m_board[y][x], true);
    m_board[y][x].setType(pt); 
    recalculateScore(m_board[y][x], false);
    return *this;
}

Board& Board::remove(int x, int y) 
{
    Piece p = m_board[y][x];
    recalculateScore(p, true);
    m_board[y][x].setType(PieceType::EMPTY); 
    return *this;
}

Board& Board::move(int x, int y, int xdest, int ydest)
{
    assert(x < 8 && y < 8 && xdest < 8 && ydest < 8 && x >=0 && y >= 0 && xdest >= 0 && ydest >= 0);

    Piece p = m_board[ydest][xdest];
    recalculateScore(p, true);
    m_board[y][x].setMoved();
    m_board[ydest][xdest] = m_board[y][x];
    m_board[y][x].setType(PieceType::EMPTY);

    return *this;
}

bool Board::operator == (Board const& other) const
{
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if(m_board[i][j].getType() != other.m_board[i][j].getType() || 
               m_board[i][j].isWhite() != other.m_board[i][j].isWhite())
                return false;
        }
    }
    return true;
}

std::ostream& operator << (std::ostream& out, Board const& board)
{
    boardArrPtr pieces = board.getPieces();

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            out << (*pieces)[i][j].getType();
        }
        out << std::endl;
    }
    return out;
}