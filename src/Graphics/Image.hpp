#ifndef DEVA_FRAMEWORK_GRAPHICS_IMAGES_IMAGE_H
#define DEVA_FRAMEWORK_GRAPHICS_IMAGES_IMAGE_H

#include "Config.hpp"

namespace DevaFramework
{

///A 32 bit image, with defined width and height, stored as a sequence of bytes, where each 4 bytes represent an RGBA value set
struct Image
{
    /** Create an Image object from a file, treating it as a specified format
        @param filename The name of the file, the image is stored in
        @param format The format of the image (Supported formats specified in ImageFormat)
    */
    static DEVA_API Image loadImageFromFile(const std::string &filename, ImageFormat format);

private:
    char* data;
public:

    unsigned int width;
    unsigned int height;

    ///Constructs an empty image
	DEVA_API Image();
    ///Constructs a deep copy of img
	DEVA_API Image(const Image &img);
    ///Transfers ownership of the data from img
	DEVA_API Image(Image &&img);

    ///Releases any currently used resources and constructs a deep copy of img
	DEVA_API Image& operator=(const Image &img);
    ///Releases any currently used resources and transfers ownership of the data from img
	DEVA_API Image& operator=(Image &&img);

    ///Returns an immutable pointer to the raw image data
	DEVA_API char * const getData();

	DEVA_API ~Image();
};


}

#endif // DEVA_FRAMEWORK_GRAPHICS_IMAGES_IMAGE_H
