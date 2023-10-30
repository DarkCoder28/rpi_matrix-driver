#include <iostream>

#include "led-matrix.h"

#include <boost/asio.hpp>

#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

#include "type_defs.h"
#include "commands/interpreter.h"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using rgb_matrix::Font;

using boost::asio::ip::tcp;

volatile bool interrupt_received = false;
static void InterruptHandler(int) {
    interrupt_received = true;
}

static int Receive(RGBMatrix *matrix, Canvas *canvas) {
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("192.168.1.64", "4000");
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);
        while (!interrupt_received) {
            char buff[10];
            boost::system::error_code error;
            socket.read_some(boost::asio::buffer(buff), error);
            if (error == boost::asio::error::eof) {
                printf("Server disconnected.\n");
                break;
            }
            interpret(matrix, canvas, buff);
        }
        return EXIT_SUCCESS;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

int main(int argc, char *argv[])
{
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "adafruit-hat";
    defaults.rows = 32;
    defaults.cols = 64;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.brightness = 100;
    defaults.pwm_dither_bits = 0;
    // defaults.show_refresh_rate = true;
    RGBMatrix *matrix = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (matrix == NULL)
        return 1;
    Canvas *canvas  = matrix;
    canvas->Fill(0,0,0);
    
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    board_state.brightness = 0;
    board_state.colour = {255, 255, 255};
    board_state.font_name = std::string("5x8");
    if (!board_state.font.LoadFont("assets/fonts/5x8.bdf")) {
        printf("Couldn't load font (5x8) at (assets/fonts/5x8.bdf)");
        return EXIT_FAILURE;
    }

    int res;
    res = Receive(matrix, canvas);
    if (res != 0) return res;

    canvas->Clear();
    delete matrix;
    delete canvas;

    return EXIT_SUCCESS;
}
