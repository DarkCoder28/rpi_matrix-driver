#include "image.h"

void draw_image(Canvas *canvas, char buff[10]) {
    std::string string = std::string(buff);
    // Extract Image Position
    int x_pos = std::stoi(string.substr(1,2));
    int y_pos = std::stoi(string.substr(3,2));
    // Extract Image Name & Path
    image_info image = extract_image_info(string.substr(5,5));
    printf("Drawing image (%s) at (%d, %d) from (%s)\n", image.name.c_str(), x_pos, y_pos, image.path.c_str());
    // Import the Image Using boost::GIL
    rgb8_image_t img;
    read_image(image.path, img, bmp_tag());
    rgb8c_view_t img_view = boost::gil::view(img);
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            uint8_t r = get_color(img_view(x, y),red_t());
            uint8_t g = get_color(img_view(x, y),green_t());
            uint8_t b = get_color(img_view(x, y),blue_t());
            if (r == 0 && g == 0 && b == 0) continue;
            canvas->SetPixel(x_pos+x, y_pos+y, r, g, b);
        }
    }
}

image_info extract_image_info(std::string name) {
    std::string image_path = std::string("assets/");
    std::string image_name;
    if (name.c_str()[0] == '^') {
        switch (name.c_str()[1]) {
            // ^1   weather_20
            case '1':
                image_path.append("weather_20/");
                image_name = name.substr(2,3);
                break;
            // ^2   weather_22
            case '2':
                image_path.append("weather_22/");
                image_name = name.substr(2,3);
                break;
            // ^i   icons
            case 'i':
                image_path.append("icons/");
                image_name = name.substr(2,3);
                break;
            
            default:
                break;
        }
    } else {
        // image_of_the_day
        image_path.append("image_of_the_day/");
        image_name = name;
    }
    // Remove extra '=' characters
    std::string::size_type first_equals = image_name.find('=');
    if (first_equals != std::string::npos) image_name = image_name.substr(0,first_equals);
    image_path.append(image_name);
    image_path.append(".bmp");
    return {image_name, image_path};
}