#pragma once

struct Chessman {
    char symbol;
    int color;
};

const int SIZE_BOARD = 8;

void create_init_chess_board(Chessman board[][SIZE_BOARD]);
