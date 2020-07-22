#include "Piece.h"
#include<cassert>

Piece::Piece(bool _isWhite, char _type)
:m_isWhite(_isWhite), m_type(_type), m_hasMoved(false) {}

void Piece::move(std::pair<int, int> p)
{
    assert(p.first < 8 && p.second < 8);
    m_position = p;
}