#include "interpreter.h"

void interpret(RGBMatrix *matrix, Canvas *canvas, char buff[10]) {
    int cmd = (int)buff[0];
    if (board_state.brightness == 0) {
        canvas->Clear();
        if (cmd == 0x62) set_brightness(matrix, buff);
        return;
    }
    switch (cmd)
    {
    case 0x78:          //  x=========    clear
        printf("\nRendering...\n");
        clear(canvas);
        break;
    case 0x62:          //  bXXX======    set brightness
        set_brightness(matrix, buff);
        break;
    case 0x63:          //  cRGB======    set colour
        set_colour(buff);
        break;
    case 0x6C:          //  lXXYYZZAA=    line
        draw_line(canvas, buff);
        break;
    case 0x70:          //  pXXYY=====    point
        draw_pixel(canvas, buff);
        break;
    case 0x71:          //  qXXYYRGB==    coloured pixel
        draw_coloured_pixel(canvas, buff);
        break;
    case 0x66:          //  fNAME=====    set font
        set_font(buff);
        break;
    case 0x74:          //  tXXYYC==== (character)
    case 0x6A:          //  jXXYYC==== (special character)
        draw_character(canvas, buff);
        break;
    case 0x69:          //  iXXYYNAME=    font image
        draw_image(canvas, buff);
        break;
    case 0x49:          //  INAME=====    image of the day
        draw_image_of_day(canvas, buff);
        break;
    case 0x73:          //  s=========    sync/done frame
    printf("Done.\n");
        break;

    default:
        printf("%s", buff);
        printf("\n");
        break;
    }
}