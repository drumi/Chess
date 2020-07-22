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

    CHECK(MoveValidator::isValid(b, 1, 0, 2, 2));
    CHECK(MoveValidator::isValid(b, 1, 0, 0, 2));
    CHECK_FALSE(MoveValidator::isValid(b, 1, 0, 1, 2));
}

TEST_CASE("rook movement validator")
{
    Board b;
    b.move(0,1,2,2);

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


int main()
{
    doctest::Context().run();

    return 0;
}