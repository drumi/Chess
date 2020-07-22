#pragma once
#include<utility>

class Piece
{
    private:
    bool m_hasMoved;
    bool m_isWhite;
    char m_type;
    std::pair<int,int> m_position;

    public:
    Piece(bool _isWhite = true, char _type = '\0');

    bool isWhite() const { return m_isWhite; }
    bool hasMoved() const { return m_hasMoved; }
    char getType() const { return m_type; }
    std::pair<int,int> getPosition() const { return m_position; }
    void move(std::pair<int, int> p);
};