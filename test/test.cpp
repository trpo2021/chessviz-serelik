#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "libchess/chess.h"
#include "libchess/chessman.h"
#include "libchess/figure.h"

struct Chessman test_board[SIZE_BOARD][SIZE_BOARD];

const int WHITE = 0;
const int RED = 31;

void create_empty_board(Chessman test_board[SIZE_BOARD][SIZE_BOARD])
{
    for (int i = 0; i < SIZE_BOARD; i++) {
        for (int j = 0; j < SIZE_BOARD; j++) {
            test_board[i][j].symbol = ' ';
            test_board[i][j].color = -1;
        }
    }
}

TEST_CASE("pawn", "")
{
    create_empty_board(test_board);

    SECTION("pawn e2-e4")
    {
        test_board[1][4].symbol = 'P';
        test_board[1][4].color = WHITE;
        CHECK(move_and_attack_pawn(test_board, 4, 1, 4, 3) == 0);
    }

    SECTION("pawn d7-d5")
    {
        test_board[6][3].symbol = 'P';
        test_board[6][3].color = RED;
        CHECK(move_and_attack_pawn(test_board, 3, 6, 3, 4) == 0);
    }

    SECTION("pawn attack e4-d5")
    {
        test_board[3][4].symbol = 'P';
        test_board[3][4].color = WHITE;
        test_board[4][3].symbol = 'P';
        test_board[4][3].color = RED;
        CHECK(move_and_attack_pawn(test_board, 4, 3, 3, 4) == 0);
    }

    SECTION("pawn move one forward c7-c6")
    {
        test_board[6][2].symbol = 'P';
        test_board[6][2].color = RED;
        CHECK(move_and_attack_pawn(test_board, 2, 6, 2, 5) == 0);
    }

    SECTION("pawn move back d5-d4")
    {
        test_board[4][3].symbol = 'P';
        test_board[4][3].color = WHITE;
        CHECK(move_and_attack_pawn(test_board, 3, 4, 3, 3) == 1);
    }

    SECTION("pawn move left b6-a6")
    {
        test_board[5][1].symbol = 'P';
        test_board[5][1].color = RED;
        CHECK(move_and_attack_pawn(test_board, 1, 5, 1, 5) == 1);
    }
}

TEST_CASE("Rook", "")
{
    create_empty_board(test_board);

    SECTION("Rook a1-a3(rook is not a horse)")
    {
        test_board[0][0].symbol = 'R';
        test_board[0][0].color = WHITE;
        test_board[1][0].symbol = 'P';
        test_board[1][0].color = WHITE;
        CHECK(rook_move(test_board, 0, 0, 0, 2) == 1);
    }

    SECTION("Rook a1-a2 (rook cant eat allies)")
    {
        test_board[0][0].symbol = 'R';
        test_board[0][0].color = WHITE;
        test_board[1][0].symbol = 'P';
        test_board[1][0].color = WHITE;
        CHECK(rook_move(test_board, 0, 0, 0, 1) == 3);
    }

    SECTION("Rook a1-a7 (rook eat)")
    {
        test_board[0][0].symbol = 'R';
        test_board[0][0].color = WHITE;
        test_board[6][0].symbol = 'P';
        test_board[6][0].color = RED;
        CHECK(rook_move(test_board, 0, 0, 0, 6) == 0);
    }

    SECTION("Rook a1-a5 (rook move vertical)")
    {
        test_board[0][0].symbol = 'R';
        test_board[0][0].color = WHITE;
        CHECK(rook_move(test_board, 0, 0, 0, 4) == 0);
    }

    SECTION("Rook a3-h3 (rook move horizontal)")
    {
        test_board[0][0].symbol = 'R';
        test_board[0][0].color = WHITE;
        CHECK(rook_move(test_board, 0, 0, 7, 0) == 0);
    }
}

TEST_CASE("Bishop", "")
{
    create_empty_board(test_board);

    SECTION("bishop c1-e3(Bishop is not a horse)")
    {
        test_board[0][2].symbol = 'B';
        test_board[0][2].color = WHITE;
        test_board[1][3].symbol = 'P';
        test_board[1][3].color = WHITE;
        CHECK(bishop_move(test_board, 2, 0, 4, 2) == 1);
    }

    SECTION("bishop a1-a5 (Bishop move cant vertical)")
    {
        test_board[0][0].symbol = 'B';
        test_board[0][0].color = WHITE;
        CHECK(bishop_move(test_board, 0, 0, 0, 4) == 1);
    }

    SECTION("Bishop a3-h3 (Bishop cant move horizontal)")
    {
        test_board[0][0].symbol = 'B';
        test_board[0][0].color = WHITE;
        CHECK(bishop_move(test_board, 0, 0, 7, 0) == 1);
    }

    SECTION("bishop a1-h8 (Bishop move)")
    {
        test_board[0][0].symbol = 'B';
        test_board[0][0].color = WHITE;
        CHECK(bishop_move(test_board, 0, 0, 7, 7) == 0);
    }

    SECTION("Bishop h1-a8 (Bishop move)")
    {
        test_board[0][7].symbol = 'B';
        test_board[0][7].color = WHITE;
        CHECK(bishop_move(test_board, 7, 0, 0, 7) == 0);
    }

    SECTION("Bishop a8-h1 (Bishop move)")
    {
        test_board[7][0].symbol = 'B';
        test_board[7][0].color = WHITE;
        CHECK(bishop_move(test_board, 0, 7, 7, 0) == 0);
    }

    SECTION("Bishop h1-a8 (Bishop eat)")
    {
        test_board[0][7].symbol = 'B';
        test_board[0][7].color = WHITE;
        test_board[7][0].symbol = 'R';
        test_board[7][0].color = RED;
        CHECK(bishop_move(test_board, 7, 0, 0, 7) == 0);
    }
}

TEST_CASE("Knight", "")
{
    create_empty_board(test_board);

    SECTION("Knight b1-c3(Knight move)")
    {
        test_board[0][1].symbol = 'N';
        test_board[0][1].color = WHITE;
        test_board[1][1].symbol = 'P';
        test_board[1][1].color = WHITE;
        CHECK(knight_move(test_board, 1, 0, 2, 2) == 0);
    }

    SECTION("Knight c3-b1(Knight move)")
    {
        test_board[2][2].symbol = 'N';
        test_board[2][2].color = WHITE;
        test_board[1][1].symbol = 'P';
        test_board[1][1].color = WHITE;
        CHECK(knight_move(test_board, 2, 2, 1, 0) == 0);
    }

    SECTION("Knight b1-d2(Knight move)")
    {
        test_board[0][2].symbol = 'N';
        test_board[0][2].color = WHITE;
        test_board[1][2].symbol = 'P';
        test_board[1][2].color = WHITE;
        CHECK(knight_move(test_board, 2, 0, 4, 1) == 0);
    }

    SECTION("Knight b1-d2(Knight cant eat allies)")
    {
        test_board[0][2].symbol = 'N';
        test_board[0][2].color = WHITE;
        test_board[1][4].symbol = 'P';
        test_board[1][4].color = WHITE;
        CHECK(knight_move(test_board, 2, 0, 4, 1) == 3);
    }
    SECTION("Knight b1-d2(Knight eat)")
    {
        test_board[0][2].symbol = 'N';
        test_board[0][2].color = WHITE;
        test_board[1][4].symbol = 'P';
        test_board[1][4].color = RED;
        CHECK(knight_move(test_board, 2, 0, 4, 1) == 0);
    }
}

TEST_CASE("Queen", "")
{
    create_empty_board(test_board);

    SECTION("Queen a8-h1 (Queen move like Bishop)")
    {
        test_board[7][0].symbol = 'Q';
        test_board[7][0].color = WHITE;
        CHECK(queen_move(test_board, 0, 7, 7, 0) == 0);
    }

    SECTION("Queen h1-a8 (Queen eat like Bishop)")
    {
        test_board[0][7].symbol = 'Q';
        test_board[0][7].color = WHITE;
        test_board[7][0].symbol = 'R';
        test_board[7][0].color = RED;
        CHECK(queen_move(test_board, 7, 0, 0, 7) == 0);
    }

    SECTION("Queen a3-h3 (Queen move like Rook)")
    {
        test_board[0][0].symbol = 'Q';
        test_board[0][0].color = WHITE;
        CHECK(queen_move(test_board, 0, 0, 7, 0) == 0);
    }

    SECTION("Queen a3-h3 (Queen eat like Rook)")
    {
        test_board[0][0].symbol = 'Q';
        test_board[0][0].color = WHITE;
        test_board[0][7].symbol = 'R';
        test_board[0][7].color = RED;

        CHECK(queen_move(test_board, 0, 0, 7, 0) == 0);
    }

    SECTION("Queen c1-e3(Queen is not a horse)")
    {
        test_board[0][2].symbol = 'Q';
        test_board[0][2].color = WHITE;
        test_board[1][3].symbol = 'P';
        test_board[1][3].color = WHITE;
        CHECK(queen_move(test_board, 2, 0, 4, 2) == 1);
    }
}

TEST_CASE("King", "")
{
    create_empty_board(test_board);

    SECTION("king a8-b7 (King move like Bishop)")
    {
        test_board[7][0].symbol = 'K';
        test_board[7][0].color = WHITE;
        CHECK(king_move(test_board, 0, 7, 1, 6) == 0);
    }

    SECTION("Queen a1-a2 (King eat like Bishop)")
    {
        test_board[6][7].symbol = 'K';
        test_board[6][7].color = WHITE;
        test_board[7][6].symbol = 'R';
        test_board[7][6].color = RED;
        CHECK(king_move(test_board, 7, 6, 6, 7) == 0);
    }

    SECTION("King a3-b3 (king move like Rook)")
    {
        test_board[0][0].symbol = 'K';
        test_board[0][0].color = WHITE;
        CHECK(king_move(test_board, 0, 0, 1, 0) == 0);
    }

    SECTION("King a3-h3 (King eat like Rook)")
    {
        test_board[0][0].symbol = 'Q';
        test_board[0][0].color = WHITE;
        test_board[0][1].symbol = 'R';
        test_board[0][1].color = RED;

        CHECK(king_move(test_board, 0, 0, 1, 0) == 0);
    }

    SECTION("King h1-a8 (King cant move that length)")
    {
        test_board[0][7].symbol = 'K';
        test_board[0][7].color = WHITE;
        CHECK(king_move(test_board, 7, 0, 0, 7) == 1);
    }
}
