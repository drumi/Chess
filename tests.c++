#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_CASE("1")
{
    CHECK(1 != 1);
}

int main()
{
    doctest::Context().run();

    return 0;
}