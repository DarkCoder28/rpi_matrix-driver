#include "pixel.h"

void draw_pixel(Canvas *canvas, char buff[10]) {
    std::string string = std::string(buff);
    int x = std::stoi(string.substr(1,2));
    int y = std::stoi(string.substr(3,2));
    Color col = board_state.colour;
    printf("Setting pixel (%d, %d) to current colour\n", x, y);
    canvas->SetPixel(x,y,col.r,col.g,col.b);
}

void draw_coloured_pixel(Canvas *canvas, char buff[10]) {
    std::string string = std::string(buff);
    // Get Point
    int x = std::stoi(string.substr(1,2));
    int y = std::stoi(string.substr(3,2));
    // Get Colour
    int r = std::stoi(string.substr(5,1), NULL, 16);
    int g = std::stoi(string.substr(6,1), NULL, 16);
    int b = std::stoi(string.substr(7,1), NULL, 16);
    r*=0x10;
    g*=0x10;
    b*=0x10;
    printf("Setting pixel (%d, %d) to (%d,%d,%d)\n", x, y, r, g, b);
    canvas->SetPixel(x,y,r,g,b);
}