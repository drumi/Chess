#include "Game.h"

Game::Game()
:m_isWhiteTurn(true){}

void Game::undoMove()
{
    if(!m_boardHistory.empty())
    {
        m_board = m_boardHistory.top();
        m_boardHistory.pop();
        m_pieceHistory.pop();
        m_isWhiteTurn = !m_isWhiteTurn;
    }
}

bool Game::tryMove(int x, int y, int xdest, int ydest)
{
    int xEnpassant = -999;
    if(!m_pieceHistory.empty())
    {
        Tuple lastMove = m_pieceHistory.top();
        if(lastMove.pieceType == PieceType::PAWN)
            if(abs(lastMove.y - lastMove.ydest) == 2)
                xEnpassant = lastMove.x;
    }

    Piece toMove = m_board.getPiece(x, y);

    if(toMove.isWhite() != m_isWhiteTurn)
        return false;
    
    if(MoveValidator::isValid(m_board, x, y, xdest, ydest, xEnpassant))
    {
        m_board.move(x, y, xdest, ydest);

        // Handle en passant
        if(toMove.getType() == PieceType::PAWN && xdest == xEnpassant && (y == 2 && !m_isWhiteTurn || y == 5 && !m_isWhiteTurn))
            m_board.remove(xdest, ydest - m_isWhiteTurn + 2 * !m_isWhiteTurn);

        // Handle castling
        if(toMove.getType() == PieceType::KING && abs(xdest - x) == 2)
            if(xdest > x)
                m_board.move(7, y, 5, y);
            else
                m_board.move(0, y, 3, y);

        m_pieceHistory.push({toMove.getType(), x, y, xdest, ydest});
        m_boardHistory.push(m_board);
        m_isWhiteTurn = !m_isWhiteTurn;
        return true;
    } 

    return false;
}

void Game::restart()
{
    m_board = Board();
    m_isWhiteTurn = true;
    m_boardHistory = std::stack<Board>();
    m_pieceHistory = std::stack<Tuple>();
}