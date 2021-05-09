#pragma once

void init_chess_board();
void print_board();
int figure_move(
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y);

const int CODE_OK = 0;
const int CODE_ILLEGAL_MOVE = 1;
const int CODE_DONT_MOVING = 2;
const int CODE_ALLIES_ATTACK = 3;
const int CODE_ANOTHER_PLAYER = 4;
