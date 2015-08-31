#include "Image.hpp"

#include "ImageReaders.hpp"

#include <glbinding/gl/gl.h>

using namespace DevaFramework;

Image Image::loadImageFromFile(const std::string &filename, ImageFormat format)
{
    RawImage raw;

    switch(format)
    {
    case PNG :
    {
        raw = readPNG(filename);
    }
    break;
    }

    if(raw.error)
    {
        return Image();
    }

    Image img;
    img.width = raw.width;
    img.height = raw.height;

    if(raw.color_type == COLOR_TYPE_RGBA && raw.bitdepth == 32)
    {
        img.data = raw.data;
        return img;
    }

    return Image();

}

Image::Image()
{
    this->data = 0;
    this->width = 0;
    this->height = 0;
}

Image::Image(const Image &img) : width(img.width), height(img.height)
{
    unsigned long int image_size = width * height * DEVA_IMAGE_BITS_PER_PIXEL / 8;

    this->data = new char[image_size];

    for(int i = 0; i<image_size; i++) this->data[i] = img.data[i];
}

Image::Image(Image &&img) : width(img.width), height(img.height)
{
    this->data = img.data;
    img.data = 0;
}

Image& Image::operator=(const Image& img)
{
    this->width = img.width;
    this->height = img.height;
    unsigned long int image_size = width * height * DEVA_IMAGE_BITS_PER_PIXEL / 8;

    if(!this->data) delete [] this->data;

    this->data = new char[image_size];

    for(int i=0; i<image_size ; i++) this->data[i] = img.data[i];

    return *this;
}

Image& Image::operator=(Image &&img)
{
    this->width = img.width;
    this->height = img.height;
    unsigned long int image_size = width * height * DEVA_IMAGE_BITS_PER_PIXEL / 8;

    if(!this->data) delete [] this->data;

    this->data = img.data;

    img.data = 0;
    return *this;
}

Image::~Image()
{
    if(this->data) delete [] this->data;
}
