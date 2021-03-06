#include "libchess/chess.h"
#include <iostream>
#include <string>

using namespace std;

bool is_letter_from_a_to_h(const char& c)
{
    return c >= 'a' && c <= 'h';
}

bool is_digit_from_1_to_8(const int& d)
{
    return d >= 1 && d <= 8;
}

int data_in_check(char& start_x, int& start_y, char& final_x, int& final_y)
{
    string input_str;
    getline(cin, input_str);

    if (input_str.compare("exit") == 0) {
        return 1;
    } else if (input_str.size() != 5) {
        printf("Incorrecnt input! for example \"e2-e4\"\n");
        return 2;
    }

    start_x = input_str.at(0);
    start_y = input_str.at(1) - '0';

    final_x = input_str.at(3);
    final_y = input_str.at(4) - '0';

    if (!is_letter_from_a_to_h(start_x) || !is_letter_from_a_to_h(final_x)) {
        printf("Incorrecnt input! Letter can be only from a to h! for "
               "example \"e2-e4\"\n");
        return 2;
    }

    if (!is_digit_from_1_to_8(start_y) || !is_digit_from_1_to_8(final_y)) {
        printf("Incorrecnt input! Digit can be only from 1 to 8! for "
               "example \"e2-e4\"\\n");
        return 2;
    }

    start_x -= 'a';
    start_y -= 1;
    final_x -= 'a';
    final_y -= 1;

    return 0;
}

int main()
{
    init_chess_board();
    print_board();

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
