#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "libchess/chess.h"
#include "libchess/chessman.h"
#include "libchess/figure.h"

struct Chessman test_board[SIZE_BOARD][SIZE_BOARD];

TEST_CASE("pawn", "")
{
    create_init_chess_board(test_board);

    SECTION("pawn e2-e4")
    {
        CHECK(pawn_move(test_board, 4, 1, 4, 3) == 0);
    }

    SECTION("pawn d7-d5")
    {
        CHECK(pawn_move(test_board, 3, 6, 3, 4) == 0);
    }

    SECTION("pawn attack e4-d5")
    {
        CHECK(pawn_move(test_board, 4, 3, 3, 4) == 0);
    }

    SECTION("pawn move one forward c7-c6")
    {
        CHECK(pawn_move(test_board, 2, 6, 2, 5) == 0);
    }

    SECTION("pawn move back d5-d4")
    {
        CHECK(pawn_move(test_board, 3, 4, 3, 3) == 1);
    }

    SECTION("pawn move left b6-a6")
    {
        CHECK(pawn_move(test_board, 1, 5, 1, 5) == 1);
    }
}
