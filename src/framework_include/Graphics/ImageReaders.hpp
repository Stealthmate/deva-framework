#ifndef DEVA_FRAMEWORK_GRAPHICS_IMAGE_READERS_H
#define DEVA_FRAMEWORK_GRAPHICS_IMAGE_READERS_H

#include "Image.hpp"

namespace DevaFramework
{

///Stores raw image data with information about width, height, channels, bitdepth and color_type
struct RawImage
{
    static const short ERROR_CANNOT_OPEN_FILE = 1;
    static const short ERROR_NOT_PNG = 2;
    static const short ERROR_LIBPNG_FAIL = 3;
    static const short ERROR_PNG_COLOR_TYPE_PALETTE = 4;

    unsigned short error = 0;

    char* data = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int channels = 0;
    unsigned int bitdepth = 0;
    unsigned int color_type = 0;
};

///Returns a RawImage, read from a PNG file
DEVA_FRAMEWORK_API RawImage readPNG(const std::string &filename);
DEVA_FRAMEWORK_API RawImage readBMP(const std::string &filename);

}

#endif // DEVA_FRAMEWORK_GRAPHICS_IMAGES_IMAGE_READERS_H
