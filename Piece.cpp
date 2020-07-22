#include "Piece.h"
#include<cassert>

Piece::Piece(bool _isWhite, PieceType _type)
:m_isWhite(_isWhite), m_type(_type), m_hasMoved(false) {}
