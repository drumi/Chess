#pragma once
#include<utility>

enum PieceType
{
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

class Piece
{
    private:
    bool m_hasMoved;
    bool m_isWhite;
    PieceType m_type;
    std::pair<int,int> m_position;

    public:
    Piece(bool _isWhite = true, PieceType _type = PieceType::PAWN);

    bool isWhite() const { return m_isWhite; }
    bool hasMoved() const { return m_hasMoved; }
    char getType() const { return m_type; }
    std::pair<int,int> getPosition() const { return m_position; }
    void move(std::pair<int, int> p);
};