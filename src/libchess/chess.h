#pragma once
#ifndef CHESS_H
#define CHESS_H

void init_chess_board();
void print_board();
int figure_move(
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y);

#endif
