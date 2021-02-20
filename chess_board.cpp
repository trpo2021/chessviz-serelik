#include <iostream>
using namespace std;

void set_red_text()
{
    printf("\x1b[31m");
}

void set_blue_text()
{
    printf("\x1b[34m");
}

void set_white_text()
{
    printf("\x1b[0m");
}

void print_initial_chess_board()
{
    set_blue_text();
    printf("%2c", ' ');
    for (int i = 0; i < 8; i++) {
        printf("%2c", 'A' + i);
    }
    printf("\n");
    set_white_text();

    for (int i = 8; i > 0; i--) {
        set_blue_text();
        printf("%2d", i);
        set_white_text();

        switch (i) {
        case 8:
            set_red_text();
        case 1:
            for (int j = 0; j <= 8; j++) {
                switch (j) {
                case 1:
                case 8:
                    printf("%2c", 'R');
                    break;
                case 2:
                case 7:
                    printf("%2c", 'N');
                    break;
                case 3:
                case 6:
                    printf("%2c", 'B');
                    break;
                case 4:
                    printf("%2c", 'Q');
                    break;
                case 5:
                    printf("%2c", 'K');
                    break;
                }
            }

            set_white_text();
            break;
        case 7:
            set_red_text();
        case 2:
            for (int i = 0; i < 8; i++) {
                printf("%2c", 'P');
            }

            set_white_text();
            break;
        }

        printf("\n");
    }
}

int main()
{
    print_initial_chess_board();
    return 0;
}
