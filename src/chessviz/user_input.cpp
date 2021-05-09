#include <iostream>
#include <string>

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
    std::string input_str;
    getline(std::cin, input_str);

    if (input_str.compare("exit") == 0) {
        return 1;
    } else if (input_str.size() != 5 || input_str.at(2) != '-') {
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
