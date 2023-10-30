#pragma once
#include "led-matrix.h"
#include "../type_defs.h"
#include <string>

using rgb_matrix::Canvas;
using rgb_matrix::DrawLine;
using rgb_matrix::Color;

void draw_line(Canvas *canvas, char buff[10]);