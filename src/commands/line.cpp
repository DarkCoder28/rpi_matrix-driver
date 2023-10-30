#include "line.h"

void draw_line(Canvas *canvas, char buff[10]) {
    std::string string = std::string(buff);
    int x = std::stoi(string.substr(1,2));
    int y = std::stoi(string.substr(3,2));
    int x2 = std::stoi(string.substr(5,2));
    int y2 = std::stoi(string.substr(7,2));
    Color col = board_state.colour;
    printf("Drawing line from (%d, %d) to (%d, %d)\n", x, y, x2, y2);
    DrawLine(canvas, x, y,x2, y2, col);
}