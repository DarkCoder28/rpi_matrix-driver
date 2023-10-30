#pragma once
#include "led-matrix.h"
#include "../type_defs.h"
#include <string>

using rgb_matrix::Canvas;
using rgb_matrix::Color;

void draw_pixel(Canvas *canvas, char buff[10]);
void draw_coloured_pixel(Canvas *canvas, char buff[10]);