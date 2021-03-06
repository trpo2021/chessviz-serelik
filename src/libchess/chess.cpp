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

int figure_move(
        const int& start_x,
        const int& start_y,
        const int& final_x,
        const int& final_y)
{
    switch (board[start_y][start_x].symbol) {
    case ' ':
        return 1;
    case 'P':
        printf("choosed pawn\n");
        break;
    default:
        printf("another figure moves are not supported yet\n");
    }

    printf("%d %d\n", final_x, final_y);
    return 0;
}
