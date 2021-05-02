#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("sum calculation", "")
{
    SECTION("sum 1")
    {
        CHECK(2 + 2 == 4);
    }

    SECTION("sum 2")
    {
        CHECK(2 + 5 == 4);
    }
}
