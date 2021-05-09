#include <cstdlib>
#include <libchess/chess.h>
#include <libchess/chessman.h>
#include <stdio.h>

const int WHITE = 0;
const int RED = 31;
const int BLUE = 34;

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

void create_init_chess_board(Chessman board[SIZE_BOARD][SIZE_BOARD])
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
            board[i][j] = {' ', BLUE};
        }
    }
}

void init_chess_board()
{
    create_init_chess_board(board);
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

void print_board(Chessman board[SIZE_BOARD][SIZE_BOARD])
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

bool is_coordinates_different(
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    return start_x != final_x || start_y != final_y;
}

bool is_attack_allies(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    if (board[start_y][start_x].color == board[final_y][final_x].color) {
        printf("cant attack allies \n");
        return true;
    }

    return false;
}

void figure_transfer(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    board[final_y][final_x] = board[start_y][start_x];
    board[start_y][start_x] = {' ', BLUE};
}

int pawn_move(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
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

        figure_transfer(board, start_x, start_y, final_x, final_y);
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

        figure_transfer(board, start_x, start_y, final_x, final_y);
        return 0;
    }

    printf("impossible pawn move\n");
    return 1;
}

int pawn_attack(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
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
            if (is_attack_allies(board, start_x, start_y, final_x, final_y)) {
                return 1;
            }

            figure_transfer(board, start_x, start_y, final_x, final_y);
            return 0;
        }
    } else {
        printf("pawn cant make back attack\n");
        return 1;
    }

    printf("impossible pawn attack\n");
    return 1;
}

int move_and_attack_pawn(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    switch (start_x - final_x) {
    case 0:
        return pawn_move(board, start_x, start_y, final_x, final_y);
    case -1:
    case 1:
        return pawn_attack(board, start_x, start_y, final_x, final_y);
    default:
        printf("impossible pawn move or attack\n");
    }
    return 0;
}

int rook_move(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    char move_coordinate_line;
    bool is_increase;
    int i, final_coordinate;

    if (start_x == final_x && start_y != final_y) {
        move_coordinate_line = 'y';
        is_increase = final_y > start_y;
        i = start_y;
        final_coordinate = final_y;
    } else if (start_x != final_x && start_y == final_y) {
        move_coordinate_line = 'x';
        is_increase = final_x > start_x;
        i = start_x;
        final_coordinate = final_x;
    } else {
        printf("Rook cant move like that\n");
        return 1;
    }

    if (is_attack_allies(board, start_x, start_y, final_x, final_y)) {
        return 1;
    }

    while (true) {
        if (is_increase) {
            i++;
        } else {
            i--;
        }

        if (i == final_coordinate) {
            break;
        }

        char symbol;

        if (move_coordinate_line == 'y') {
            symbol = board[i][start_x].symbol;
        } else {
            symbol = board[start_y][i].symbol;
        }

        if (symbol != ' ') {
            printf("it is not horse\n");
            return 1;
        }
    }

    figure_transfer(board, start_x, start_y, final_x, final_y);
    return 0;
}

int bishop_move(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    if (abs(final_y - start_y) != abs(final_x - start_x)) {
        printf("bishop cant move like that\n");
        return 1;
    }

    if (is_attack_allies(board, start_x, start_y, final_x, final_y)) {
        return 1;
    }

    bool is_increase_x = final_x > start_x;
    bool is_increase_y = final_y > start_y;
    int i_x = start_x, i_y = start_y;

    while (true) {
        if (is_increase_x) {
            i_x++;
        } else {
            i_x--;
        }

        if (is_increase_y) {
            i_y++;
        } else {
            i_y--;
        }

        if (i_x == final_x) {
            break;
        }

        if (board[i_y][i_x].symbol != ' ') {
            printf("it is not horse\n");
            return 1;
        }
    }

    figure_transfer(board, start_x, start_y, final_x, final_y);
    return 0;
}

int knight_move(
        Chessman board[SIZE_BOARD][SIZE_BOARD],
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    int x_diff = abs(final_x - start_x);
    int y_diff = abs(final_y - start_y);

    if ((x_diff == 1 && y_diff == 2) || (x_diff == 2 && y_diff == 1)) {
        if (is_attack_allies(board, start_x, start_y, final_x, final_y)) {
            return 1;
        }

        figure_transfer(board, start_x, start_y, final_x, final_y);
        return 0;
    }

    printf("horse cant move like that\n");
    return 1;
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

    if (is_coordinates_different(start_x, start_y, final_x, final_y) == false) {
        printf("figure is not moving\n");
        return 2;
    }

    int code = 1;

    switch (board[start_y][start_x].symbol) {
    case ' ':
        printf("you shoosed empty cell\n");
        code = 1;
        break;
    case 'P':
        code = move_and_attack_pawn(board, start_x, start_y, final_x, final_y);
        break;
    case 'R':
        code = rook_move(board, start_x, start_y, final_x, final_y);
        break;
    case 'B':
        code = bishop_move(board, start_x, start_y, final_x, final_y);
        break;
    case 'N':
        code = knight_move(board, start_x, start_y, final_x, final_y);
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
