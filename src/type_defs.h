#pragma once
#include <string>
#include "led-matrix.h"

struct State {
    std::string font_name;
    rgb_matrix::Font font;
    int brightness;
    rgb_matrix::Color colour;
};

extern State board_state;