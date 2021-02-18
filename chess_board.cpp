#include <iostream>
using namespace std;

void print_initial_chess_board()
{
    printf("%2c", ' ');
    for (int i = 0; i < 8; i++) {
        printf("%2c", 'A' + i);
    }
    printf("\n");

    for (int i = 1; i <= 8; i++) {
        printf("%2d", i);

        switch (i) {
        case 1:
        case 8:
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
            break;
        case 2:
        case 7:
            for (int i = 0; i < 8; i++) {
                printf("%2c", 'P');
            }
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
