#pragma once

int move_and_attack_pawn(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y);

int rook_move(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y);

int bishop_move(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y);

int knight_move(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y);

int queen_move(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y);

int king_move(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y);
