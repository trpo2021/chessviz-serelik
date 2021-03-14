#include "libchess/chess.h"
#include "user_input.h"

int main()
{
    init_chess_board();
    print_board();

    char start_x;
    int start_y;
    char final_x;
    int final_y;

    while (true) {
        int code = data_in_check(start_x, start_y, final_x, final_y);
        if (code == 1) {
            break;
        } else if (code == 2) {
            continue;
        }

        code = figure_move(start_x, start_y, final_x, final_y);

        if (code == 0) {
            print_board();
        } else {
            continue;
        }
    }

    return 0;
}
