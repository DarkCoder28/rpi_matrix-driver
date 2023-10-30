#pragma once
#include "led-matrix.h"
#include "../type_defs.h"
#include <string>
#include <sys/stat.h>

using rgb_matrix::Canvas;
using rgb_matrix::DrawText;
using rgb_matrix::Font;
using rgb_matrix::Color;

using std::string;

void set_font(char buff[10]);
void draw_character(Canvas *canvas, char buff[10]);