#include <libchess/chess.h>
#include <stdio.h>

void show_error(int code)
{
    switch (code) {
    case CODE_ILLEGAL_MOVE:
        printf("figure cant move like that\n");
        break;
    case CODE_DONT_MOVING:
        printf("figure is not moving\n");
        break;
    case CODE_ALLIES_ATTACK:
        printf("cant attack allies \n");
        break;
    case CODE_ANOTHER_PLAYER:
        printf("it's another player's turn \n");
        break;
    default:
        printf("unknown error\n");
    }
}
