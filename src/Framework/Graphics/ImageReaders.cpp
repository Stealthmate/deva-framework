#include "ImageReaders.hpp"

#include <fstream>
#include "../Exceptions.hpp"
#include <iostream>
using namespace DevaFramework;

#include <libpng/png.h>

static void readData(png_structp pngPtr, png_bytep data, png_size_t length)
{
    png_voidp a = png_get_io_ptr(pngPtr);
    ((std::istream*)a)->read((char*)data, length);
}


RawImage DevaFramework::readPNG(const std::string &filename)
{
    std::ifstream source(filename, std::ios::in | std::ios::binary);
    RawImage raw_data;

    if(!source.is_open())
    {
		throw DevaInvalidInputException("Image does not found. (" + filename + ")");
    }

    png_byte png_signature[8];
    int is_not_png = 0;
    source.read((char*)png_signature, 8);

    is_not_png = png_sig_cmp(png_signature, 0, 8);
    if(is_not_png)
    {
		throw DevaInvalidInputException("readPNG: Image is not PNG.");

    }

    png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr)
    {
		throw DevaInvalidInputException("readPNG: libPNG failed. (Could not create read_struct)");
    }

    png_infop infoPtr = png_create_info_struct(pngPtr);

    if (!infoPtr)
    {
        png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
		throw DevaInvalidInputException("readPNG: libPNG failed. (Could not create info_struct)");
    }


    png_bytep* rowPtrs = NULL;
    byte_t* data = NULL;

    png_set_read_fn(pngPtr,(png_voidp)&source, readData);

    png_set_sig_bytes(pngPtr, 8);

    png_read_info(pngPtr, infoPtr);

    png_uint_32 imgWidth   =  png_get_image_width(pngPtr, infoPtr);
    png_uint_32 imgHeight  = png_get_image_height(pngPtr, infoPtr);
    png_uint_32 bitdepth   = png_get_bit_depth(pngPtr, infoPtr);
    png_uint_32 channels   = png_get_channels(pngPtr, infoPtr);
    png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);

    raw_data.width = imgWidth;
    raw_data.height = imgHeight;
    raw_data.bitdepth = bitdepth;
    raw_data.channels = channels;
    raw_data.color_type = color_type;

    rowPtrs = new png_bytep[imgHeight];

    data = new byte_t[imgWidth * imgHeight * bitdepth * channels / 8];

    const unsigned int stride = imgWidth * bitdepth * channels / 8;

    for (size_t i = 0; i < imgHeight; i++)
    {
        png_uint_32 q = (png_uint_32) ((imgHeight- i - 1) * stride);
        rowPtrs[i] = (png_bytep)data + q;
    }

    png_read_image(pngPtr, rowPtrs);

    delete[] (png_bytep)rowPtrs;
    png_destroy_read_struct(&pngPtr, &infoPtr,(png_infopp)0);

    raw_data.data = (char*)data;

    source.close();

    return raw_data;
}
