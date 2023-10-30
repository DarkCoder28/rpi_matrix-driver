#pragma once
#include "led-matrix.h"
#include "../type_defs.h"
#include <string>

using rgb_matrix::RGBMatrix;

void set_brightness(RGBMatrix *matrix, char buff[10]);