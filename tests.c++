#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "MoveValidator.h"
#include <cassert>

TEST_CASE("pawn validator test")
{
    Board b;

    for (size_t i = 0; i < 8; i++)
    {
        CHECK(MoveValidator::isValid(b, i, 1, i, 2));
        CHECK(MoveValidator::isValid(b, i, 1, i, 3));

        CHECK_FALSE(MoveValidator::isValid(b, i, 1, i, 0));
        CHECK_FALSE(MoveValidator::isValid(b, i, 1, i+1, 2));
        CHECK_FALSE(MoveValidator::isValid(b, i, 1, i, 4));
    }

    b.move(6,6,6,2);

    CHECK(MoveValidator::isValid(b, 5, 1, 6, 2));
    CHECK_FALSE(MoveValidator::isValid(b, 6, 1, 6, 2));
    CHECK(MoveValidator::isValid(b, 7, 1, 6, 2));

    b.move(1,1,2,2);

    CHECK_FALSE(MoveValidator::isValid(b, 2, 1, 2, 2));

}

TEST_CASE("knight movement validator")
{
    Board b;
    assert(((*b.getPieces())[0][1].getType() == PieceType::KNIGHT));

    CHECK(MoveValidator::isValid(b, 1, 0, 2, 2));
    CHECK(MoveValidator::isValid(b, 1, 0, 0, 2));
    CHECK_FALSE(MoveValidator::isValid(b, 1, 0, 1, 2));
}

TEST_CASE("rook movement validator")
{
    Board b;
    b.move(0,1,2,2);
    assert(((*b.getPieces())[0][0].getType() == PieceType::ROOK));
    
    CHECK(MoveValidator::isValid(b, 0, 0, 0, 4));
    CHECK(MoveValidator::isValid(b, 0, 0, 0, 6));
    CHECK_FALSE(MoveValidator::isValid(b, 0, 0, 1, 0));
    CHECK_FALSE(MoveValidator::isValid(b, 0, 0, 0, 7));
    CHECK_FALSE(MoveValidator::isValid(b, 0, 0, 1, 2));
}

TEST_CASE("bishop movement validator")
{
    Board b;
    b.move(2,0,2,2);
    assert(((*b.getPieces())[2][2].getType() == PieceType::BISHOP));
    CHECK(MoveValidator::isValid(b, 2, 2, 5, 5));
    CHECK(MoveValidator::isValid(b, 2, 2, 6, 6));
    CHECK(MoveValidator::isValid(b, 2, 2, 0, 4));
    CHECK(MoveValidator::isValid(b, 2, 2, 1, 3));
    CHECK_FALSE(MoveValidator::isValid(b, 2, 2, 7, 7));
    CHECK_FALSE(MoveValidator::isValid(b, 2, 2, 5, 4));
    CHECK_FALSE(MoveValidator::isValid(b, 2, 2, 5, 2));
    CHECK_FALSE(MoveValidator::isValid(b, 2, 2, 1, 1));
}

TEST_CASE("queen movement validator")
{
    Board b;
    b.move(3,0,4,4);
    assert(((*b.getPieces())[4][4].getType() == PieceType::QUEEN));
    CHECK(MoveValidator::isValid(b, 4, 4, 5, 5));
    CHECK(MoveValidator::isValid(b, 4, 4, 6, 6));
    CHECK(MoveValidator::isValid(b, 4, 4, 0, 4));
    CHECK(MoveValidator::isValid(b, 4, 4, 4, 6));
    CHECK(MoveValidator::isValid(b, 4, 4, 3, 5));

    CHECK_FALSE(MoveValidator::isValid(b, 4, 4, 6, 7));
    CHECK_FALSE(MoveValidator::isValid(b, 4, 4, 7, 7));
    CHECK_FALSE(MoveValidator::isValid(b, 4, 4, 1, 1));
}

TEST_CASE("king movement validator")
{
    Board b;
    b.move(4, 0, 4, 4);
    assert(((*b.getPieces())[4][4].getType() == PieceType::KING));
    CHECK(MoveValidator::isValid(b, 4, 4, 5, 5));
    CHECK(MoveValidator::isValid(b, 4, 4, 3, 3));
    CHECK(MoveValidator::isValid(b, 4, 4, 3, 4));

    CHECK_FALSE(MoveValidator::isValid(b, 4, 4, 6, 4));
    CHECK_FALSE(MoveValidator::isValid(b, 4, 4, 2, 4));
    CHECK_FALSE(MoveValidator::isValid(b, 4, 4, 1, 1));
}

TEST_CASE("casting movement validator")
{
    Board b;

    assert(((*b.getPieces())[0][4].getType() == PieceType::KING));

    b.move(1, 0, 1, 4);
    b.move(2, 0, 2, 4);
    b.move(3, 0, 3, 4);

    CHECK(MoveValidator::isValid(b, 4, 0, 2, 0));

    b.move(0, 0, 0, 4);
    b.move(0, 4, 0, 0);

    CHECK_FALSE(MoveValidator::isValid(b, 4, 0, 2, 0));


    b.move(6, 0, 6, 4);
    b.move(5, 0, 5, 4);

    CHECK(MoveValidator::isValid(b, 4, 0, 6, 0));

    b.move(4, 0, 4, 4);
    b.move(4, 4, 4, 0);

    CHECK_FALSE(MoveValidator::isValid(b, 4, 0, 6, 0));
}

int main()
{
    doctest::Context().run();

    return 0;
}