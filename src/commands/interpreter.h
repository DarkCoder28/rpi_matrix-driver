#pragma once
#include <stdio.h>
#include "led-matrix.h"
#include "../type_defs.h"

#include "clear.h"
#include "brightness.h"
#include "colour.h"
#include "line.h"
#include "pixel.h"
#include "text.h"
#include "image.h"
#include "image_of_day.h"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

void interpret(RGBMatrix *matrix, Canvas *canvas, char buff[10]);