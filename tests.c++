#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "MoveValidator.h"

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

    CHECK(MoveValidator::isValid(b, 6, 0, 6, 2));
    CHECK_FALSE(MoveValidator::isValid(b, 6, 3, 6, 2));
    CHECK(MoveValidator::isValid(b, 6, 1, 6, 2));

    b.move(1,1,2,2);

    CHECK_FALSE(MoveValidator::isValid(b, 2, 1, 2, 2));

}

int main()
{
    doctest::Context().run();

    return 0;
}