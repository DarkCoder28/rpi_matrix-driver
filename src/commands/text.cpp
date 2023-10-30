#include "text.h"

void set_font(char buff[10]) {
    // Parse font name from command
    std::string string = std::string(buff);
    int name_start = 1;
    std::string font_name = string.substr(name_start, 10-name_start);
    std::string::size_type first_equals = font_name.find('=');
    if (first_equals != std::string::npos) font_name = font_name.substr(0,first_equals);
    // Check an see if the font is already selected
    if (first_equals != std::string::npos) first_equals = font_name.length();
    font_name = font_name.substr(0,first_equals);
    // If font is not already selected, generate the font path
    std::string font_path = std::string("assets/fonts/");
    font_path.append(font_name);
    font_path.append(".bdf");
    // Check and see if the font really exists; do not change font if not.
    struct stat buffer;
    if (stat(font_path.c_str(), &buffer) == 0) {
        // Set new font name and load new font.
        board_state.font_name = font_name;
        if (!board_state.font.LoadFont(font_path.c_str())) {
            printf("Couldn't load font (%s) at (%s)\nUsing last font!\n", font_name.c_str(), font_path.c_str());
        }
        printf("Font set to (%s), found at (%s)\n", font_name.c_str(), font_path.c_str());
    } else {
        printf("Font (%s) does not exist at (%s)!\n", font_name.c_str(), font_path.c_str());
    }
}

void draw_character(Canvas *canvas, char buff[10]) {
    bool special_char = false;
    if (buff[0] == 0x6A) special_char = true;
    std::string string = std::string(buff);
    int x = std::stoi(string.substr(1,2));
    int y = std::stoi(string.substr(3,2));
    const char *character = string.substr(5,1).c_str();
    if (special_char) {
        switch ((int)buff[5])
        {
        case 0x31:              // 1 => DEGREE
            character = std::string("°").c_str();
            break;
        
        default:
            break;
        }
    }
    printf("Drawing character (%s) at (%d,%d)\n", character, x, y);

    Font &font = board_state.font;
    Color &col = board_state.colour;
    DrawText(canvas, font, x, y + font.baseline(), col, NULL, character, 0);
}