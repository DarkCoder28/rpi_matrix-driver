#pragma once
#include "led-matrix.h"
#include "../type_defs.h"
#include <boost/gil.hpp>
#include <boost/gil/extension/io/bmp.hpp>
#include <string>

using rgb_matrix::Canvas;
using rgb_matrix::Color;

using boost::gil::rgb8_image_t;
using boost::gil::rgb8c_view_t;
using boost::gil::read_image;
using boost::gil::bmp_tag;

using boost::gil::get_color;
using boost::gil::red_t;
using boost::gil::green_t;
using boost::gil::blue_t;

void draw_image_of_day(Canvas *canvas, char buff[10]);