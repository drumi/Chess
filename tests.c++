#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "MoveValidator.h"
#include "MoveGenerator.h"
#include <cassert>

TEST_CASE("pawn validator test")
{
    Board b;

    for (size_t i = 0; i < 8; i++)
    {
        CHECK(MoveValidator::isValid(b, i, 1, i, 2));
        CHECK(MoveValidator::isValid(b, i, 1, i, 3));

        CHECK_FALSE(MoveValidator::isValid(b, i, 1, i, 0));
        CHECK_FALSE(MoveValidator::isValid(b, i, 1, i + 1, 2));
        CHECK_FALSE(MoveValidator::isValid(b, i, 1, i, 4));

        CHECK(MoveValidator::isValid(b, i, 6, i, 4));
        CHECK(MoveValidator::isValid(b, i, 6, i, 5));

        CHECK_FALSE(MoveValidator::isValid(b, i, 6, i, 7));
        CHECK_FALSE(MoveValidator::isValid(b, i, 6, i + 1, 5));
        CHECK_FALSE(MoveValidator::isValid(b, i, 6, i, 3));
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
    CHECK(((*b.getPieces())[0][1].getType() == PieceType::KNIGHT));

    CHECK(MoveValidator::isValid(b, 1, 0, 2, 2));
    CHECK(MoveValidator::isValid(b, 1, 0, 0, 2));
    CHECK_FALSE(MoveValidator::isValid(b, 1, 0, 1, 2));
    CHECK_FALSE(MoveValidator::isValid(b, 1, 0, 1, -1));
    CHECK_FALSE(MoveValidator::isValid(b, 1, 7, 3, 8));
}

TEST_CASE("rook movement validator")
{
    Board b;
    b.move(0,1,2,2);
    CHECK(((*b.getPieces())[0][0].getType() == PieceType::ROOK));
    
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
    CHECK(((*b.getPieces())[2][2].getType() == PieceType::BISHOP));
    CHECK(MoveValidator::isValid(b, 2, 2, 5, 5));
    CHECK(MoveValidator::isValid(b, 2, 2, 6, 6));
    CHECK(MoveValidator::isValid(b, 2, 2, 0, 4));
    CHECK(MoveValidator::isValid(b, 2, 2, 1, 3));
    CHECK_FALSE(MoveValidator::isValid(b, 2, 2, 7, 7));
    CHECK_FALSE(MoveValidator::isValid(b, 2, 2, 5, 4));
    CHECK_FALSE(MoveValidator::isValid(b, 2, 2, 5, 2));
    CHECK_FALSE(MoveValidator::isValid(b, 2, 2, 1, 1));

    Board b4;

    b4.move(2, 7, 4, 4);
    CHECK(((*b4.getPieces())[4][4].getType() == PieceType::BISHOP));
    CHECK(MoveValidator::isValid(b4, 4, 4, 1, 1));
    CHECK(MoveValidator::isValid(b4, 4, 4, 2, 2));
    CHECK(MoveValidator::isValid(b4, 4, 4, 1, 1));
}

TEST_CASE("queen movement validator")
{
    Board b;
    b.move(3,0,4,4);
    CHECK(((*b.getPieces())[4][4].getType() == PieceType::QUEEN));
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
    CHECK(((*b.getPieces())[4][4].getType() == PieceType::KING));
    CHECK(MoveValidator::isValid(b, 4, 4, 5, 5));
    CHECK(MoveValidator::isValid(b, 4, 4, 3, 3));
    CHECK(MoveValidator::isValid(b, 4, 4, 3, 4));

    CHECK_FALSE(MoveValidator::isValid(b, 4, 4, 6, 4));
    CHECK_FALSE(MoveValidator::isValid(b, 4, 4, 2, 4));
    CHECK_FALSE(MoveValidator::isValid(b, 4, 4, 1, 1));
}

TEST_CASE("king castling movement validator")
{
    Board b;

    CHECK(((*b.getPieces())[0][4].getType() == PieceType::KING));

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

    Board b9;

    b9.move(1, 7, 1, 4);
    b9.move(2, 7, 2, 4);
    b9.move(3, 7, 3, 4);

    CHECK(MoveValidator::isValid(b9, 4, 7, 2, 7));
}

TEST_CASE("Square under attack")
{
    Board b;

    CHECK(MoveValidator::isSquareUnderAttack(b, 0, 2, false));
    CHECK(MoveValidator::isSquareUnderAttack(b, 2, 2, false));

    b.move(0, 0, 4, 4);

    CHECK(((*b.getPieces())[4][4].getType() == PieceType::ROOK));

    CHECK(MoveValidator::isSquareUnderAttack(b, 6, 4, false));
    CHECK(MoveValidator::isSquareUnderAttack(b, 2, 4, false));
    CHECK(MoveValidator::isSquareUnderAttack(b, 4, 6, false));
    CHECK(MoveValidator::isSquareUnderAttack(b, 4, 5, false));
    CHECK(MoveValidator::isSquareUnderAttack(b, 4, 2, false));

    Board b2;

    CHECK(MoveValidator::isSquareUnderAttack(b2, 0, 2, false));

    b2.move(2, 0, 4, 4);
    CHECK(((*b2.getPieces())[4][4].getType() == PieceType::BISHOP));

    CHECK(MoveValidator::isSquareUnderAttack(b2, 5, 5, false));
    CHECK(MoveValidator::isSquareUnderAttack(b2, 3, 3, false));
    CHECK(MoveValidator::isSquareUnderAttack(b2, 3, 5, false));
    CHECK(MoveValidator::isSquareUnderAttack(b2, 5, 3, false));

    Board b3;
    b3.move(3, 1, 3, 3);

    CHECK(((*b3.getPieces())[3][3].getType() == PieceType::PAWN));

    CHECK(MoveValidator::isSquareUnderAttack(b3, 4, 4, false));
    CHECK(MoveValidator::isSquareUnderAttack(b3, 2, 4, false));
    CHECK_FALSE(MoveValidator::isSquareUnderAttack(b3, 3, 4, false));

    Board b4;
    b4.move(4, 0, 3, 3);

    CHECK(((*b4.getPieces())[3][3].getType() == PieceType::KING));

    CHECK(MoveValidator::isSquareUnderAttack(b4, 2, 4, false));
    CHECK(MoveValidator::isSquareUnderAttack(b4, 3, 4, false));
    CHECK(MoveValidator::isSquareUnderAttack(b4, 4, 4, false));
    CHECK(MoveValidator::isSquareUnderAttack(b4, 2, 3, false));
    CHECK(MoveValidator::isSquareUnderAttack(b4, 4, 3, false));
    CHECK(MoveValidator::isSquareUnderAttack(b4, 2, 2, false));
    CHECK(MoveValidator::isSquareUnderAttack(b4, 3, 2, false));
    CHECK(MoveValidator::isSquareUnderAttack(b4, 4, 2, false));
}

TEST_CASE("King under attack")
{
    Board b;

    b.move(4, 0, 4, 4);
    b.move(3, 6, 3, 5);

    CHECK(((*b.getPieces())[4][4].getType() == PieceType::KING));
    CHECK(((*b.getPieces())[5][3].getType() == PieceType::PAWN));

    CHECK(MoveValidator::isKingUnderCheck(b, false));

    Board b2;

    CHECK_FALSE(MoveValidator::isKingUnderCheck(b2, false));
    
    b2.move(4, 0, 4, 4);

    CHECK_FALSE(MoveValidator::isKingUnderCheck(b2, false));

    b2.move(7, 7, 7, 4);

    CHECK(((*b2.getPieces())[4][4].getType() == PieceType::KING));
    CHECK(((*b2.getPieces())[4][7].getType() == PieceType::ROOK));

    CHECK(MoveValidator::isKingUnderCheck(b2, false));
}

TEST_CASE("Board copying")
{
    Board b, b3;

    CHECK(b3 == b);

    b.move(2, 1, 2, 3);
    b.move(6, 6, 3, 3);

    Board b2 = b;

    CHECK(b2 == b);

    b.move(0, 0, 0, 1);

    CHECK_FALSE(b2 == b);

    b2.move(0, 0, 0, 1);

}

TEST_CASE("En passant validator")
{
    Board b, b2;
    b.move(2, 1, 2, 3);
    b.move(6, 6, 3, 3);

    CHECK(MoveValidator::isValid(b, 3, 3, 2, 2, 2));

    b2.move(2, 1, 2, 3);
    b2.move(6, 6, 3, 3);

    b2.move(2, 0, 1, 2);
    b2.move(4, 7, 4, 5);

    CHECK_FALSE(MoveValidator::isValid(b2, 3, 3, 2, 2, 2));
}

TEST_CASE("Move Generate")
{
    Board b;
    auto result = MoveGenerator::Generate(b, false);

    CHECK(result.size() == 20);

    result = MoveGenerator::Generate(b, true);

    CHECK(result.size() == 20);

    Board b2;

    b2.move(0, 7, 1, 4);

    result = MoveGenerator::Generate(b2, true);

    CHECK(result.size() == 30);

    Board b3;

    b3.move(3, 7, 4, 4);

    result = MoveGenerator::Generate(b3, true);
    
    CHECK(result.size() == 39);

    Board b4;

    b4.move(2, 7, 4, 4);

    result = MoveGenerator::Generate(b4, true);
    
    CHECK(result.size() == 28);

    Board b5;

    b5.move(1, 7, 4, 3);

    result = MoveGenerator::Generate(b5, true);
    
    CHECK(result.size() == 27);
}

int main()
{
    doctest::Context().run();

    return 0;
}