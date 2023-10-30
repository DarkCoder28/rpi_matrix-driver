#include "brightness.h"

void set_brightness(RGBMatrix *matrix, char buff[10]) {
    std::string string = std::string(buff);
    int brightness = std::stoi(string.substr(1,3));
    printf("Setting brightness to: %d\n", brightness);
    if (brightness != board_state.brightness) {
        matrix->SetBrightness(brightness);
        board_state.brightness = brightness;
    }
}