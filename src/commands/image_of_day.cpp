#include "image_of_day.h"

void draw_image_of_day(Canvas *canvas, char buff[10]) {
    std::string string = std::string(buff);
    // Extract Image Name
    std::string image_name = string.substr(1,9);
    // Remove extra '=' from name
    std::string::size_type first_equals = image_name.find('=');
    if (first_equals != std::string::npos) image_name = image_name.substr(0,first_equals);
    // Extract Image Path
    std::string image_path = std::string("assets/image_of_the_day/");
    image_path.append(image_name);
    image_path.append(".bmp");
    printf("Drawing image of the day (%s) from (%s)\n", image_name.c_str(), image_path.c_str());
    // Import the Image Using boost::GIL
    rgb8_image_t img;
    read_image(image_path, img, bmp_tag());
    rgb8c_view_t img_view = boost::gil::view(img);
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            uint8_t r = get_color(img_view(x, y),red_t());
            uint8_t g = get_color(img_view(x, y),green_t());
            uint8_t b = get_color(img_view(x, y),blue_t());
            canvas->SetPixel(x, y, r, g, b);
        }
    }
}