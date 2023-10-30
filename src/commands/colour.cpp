#include "colour.h"

void set_colour(char buff[10]) {
    std::string string = std::string(buff);
    int r = std::stoi(string.substr(1,1), NULL, 16);
    int g = std::stoi(string.substr(2,1), NULL, 16);
    int b = std::stoi(string.substr(3,1), NULL, 16);
    r*=0x10;
    g*=0x10;
    b*=0x10;
    printf("Setting colour to (%d, %d, %d)\n", r, g, b);
    board_state.colour.r = r;
    board_state.colour.g = g;
    board_state.colour.b = b;
}