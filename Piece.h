#pragma once
#include<utility>

enum PieceType
{
    EMPTY,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
};

class Piece
{
    private:
    bool m_hasMoved;
    bool m_isWhite;
    PieceType m_type;
    std::pair<int,int> m_position;

    public:
    Piece(bool _isWhite = true, PieceType _type = PieceType::EMPTY);

    bool isWhite() const { return m_isWhite; }
    bool hasMoved() const { return m_hasMoved; }
    PieceType getType() const { return m_type; }
    void setMoved() { m_hasMoved = true; }
    void setType(PieceType t) { m_type = t;}
};