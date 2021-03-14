#include <libchess/chess.h>
#include <stdio.h>

const int WHITE = 0;
const int RED = 31;
const int BLUE = 34;

const int SIZE_BOARD = 8;

struct Chessman {
    char symbol;
    int color;
};

struct Chessman board[SIZE_BOARD][SIZE_BOARD];
int current_player_color = WHITE;

void change_current_player()
{
    if (current_player_color == WHITE) {
        current_player_color = RED;
    } else {
        current_player_color = WHITE;
    }
}

void set_color_text(int color)
{
    printf("\x1b[%dm", color);
}

void init_chess_board()
{
    for (int i = 0; i < SIZE_BOARD; i++) {
        board[6][i] = {'P', RED};
        board[1][i] = {'P', WHITE};
    }

    board[7][0] = {'R', RED};
    board[7][7] = {'R', RED};
    board[0][0] = {'R', WHITE};
    board[0][7] = {'R', WHITE};

    board[7][1] = {'N', RED};
    board[7][6] = {'N', RED};
    board[0][1] = {'N', WHITE};
    board[0][6] = {'N', WHITE};

    board[7][2] = {'B', RED};
    board[7][5] = {'B', RED};
    board[0][2] = {'B', WHITE};
    board[0][5] = {'B', WHITE};

    board[7][3] = {'Q', RED};
    board[0][3] = {'Q', WHITE};

    board[7][4] = {'K', RED};
    board[0][4] = {'K', WHITE};

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < SIZE_BOARD; j++) {
            board[i][j] = {' ', WHITE};
        }
    }
}

void print_board()
{
    set_color_text(BLUE);
    printf("%2c", ' ');
    for (int i = 0; i < 8; i++) {
        printf("%2c", 'A' + i);
    }
    printf("\n");
    set_color_text(WHITE);

    for (int i = SIZE_BOARD - 1; i >= 0; i--) {
        set_color_text(BLUE);
        printf("%2d", i + 1);
        set_color_text(WHITE);

        for (int j = 0; j < SIZE_BOARD; j++) {
            set_color_text(board[i][j].color);
            printf("%2c", board[i][j].symbol);
            set_color_text(WHITE);
        }

        printf("\n");
    }
}

void figure_transfer(
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    board[final_y][final_x] = board[start_y][start_x];
    board[start_y][start_x] = {' ', WHITE};
}

int pawn_move(
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    int initial_position = 1;
    int forward_direction = 1;

    if (board[start_y][start_x].color == RED) {
        initial_position = 6;
        forward_direction = -1;
    }

    if (final_y - start_y == (1 * forward_direction)) {
        if (board[final_y][final_x].symbol != ' ') {
            printf("pawn cant attack forward\n");
            return 1;
        }

        figure_transfer(start_x, start_y, final_x, final_y);
        return 0;
    }

    if (final_y - start_y == (2 * forward_direction)) {
        if (start_y != initial_position) {
            printf("You can not move on 2 cell only with start position\n");
            return 1;
        }

        if (board[start_y + (1 * forward_direction)][start_x].symbol != ' ') {
            printf("You can not jump through figure\n");
            return 1;
        }

        figure_transfer(start_x, start_y, final_x, final_y);
        return 0;
    }

    return 1;
}

int pawn_attack(
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    int forward_direction = 1;

    if (board[start_y][start_x].color == RED) {
        forward_direction = -1;
    }

    if (final_y - start_y == (1 * forward_direction)) {
        if (board[final_y][final_x].symbol != ' ') {
            if (board[start_y][start_x].color
                == board[final_y][final_x].color) {
                printf("cant attack allies \n");
                return 1;
            }

            figure_transfer(start_x, start_y, final_x, final_y);
            return 0;
        }
    } else {
        printf("pawn cant make back attack\n");
        return 1;
    }
    return 1;
}

int move_and_attack_pawn(
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    switch (start_x - final_x) {
    case 0:
        return pawn_move(start_x, start_y, final_x, final_y);
    case -1:
    case 1:
        return pawn_attack(start_x, start_y, final_x, final_y);
    default:
        printf("impossible pawn move or attack\n");
    }
    return 0;
}

int figure_move(
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    if (board[start_y][start_x].color != current_player_color) {
        printf("it's another player's turn \n");
        return 1;
    }

    int code = 1;

    switch (board[start_y][start_x].symbol) {
    case ' ':
        printf("you shoosed empty cell\n");
        code = 1;
        break;
    case 'P':
        code = move_and_attack_pawn(start_x, start_y, final_x, final_y);
        break;
    default:
        printf("another figure moves are not supported yet\n");
        code = 1;
    }

    if (code == 0) {
        change_current_player();
    }

    return code;
}
