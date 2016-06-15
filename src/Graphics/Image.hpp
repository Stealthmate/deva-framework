#ifndef DEVA_FRAMEWORK_GRAPHICS_IMAGE_H
#define DEVA_FRAMEWORK_GRAPHICS_IMAGE_H

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
    DEVA_FRAMEWORK_API static Image loadImageFromFile(const std::string &filename, ImageFormat format);

private:
    byte_t* data;
public:

    unsigned int width;
    unsigned int height;

    ///Constructs an empty image
	DEVA_FRAMEWORK_API Image();
    ///Constructs a deep copy of img
	DEVA_FRAMEWORK_API Image(const Image &img);
    ///Transfers ownership of the data from img
	DEVA_FRAMEWORK_API Image(Image &&img);

    ///Releases any currently used resources and constructs a deep copy of img
	DEVA_FRAMEWORK_API Image& operator=(const Image &img);
    ///Releases any currently used resources and transfers ownership of the data from img
	DEVA_FRAMEWORK_API Image& operator=(Image &&img);

    ///Returns an immutable pointer to the raw image data
	DEVA_FRAMEWORK_API byte_t * const getData() const;

	DEVA_FRAMEWORK_API ~Image();
};


}

#endif // DEVA_FRAMEWORK_GRAPHICS_IMAGE_H
