#ifndef DEVA_FRAMEWORK_GRAPHICS_IMAGE_H
#define DEVA_FRAMEWORK_GRAPHICS_IMAGE_H

#include "Config.hpp"
#include "../Core/DataHolder.hpp"

namespace DevaFramework
{

///A 32 bit image, with defined width and height, stored as a sequence of bytes, where each 4 bytes represent an RGBA value set
struct Image : public DataHolder<std::vector<byte_t>>
{
    /** Create an Image object from a file, treating it as a specified format
        @param filename The name of the file, the image is stored in
        @param format The format of the image (Supported formats specified in ImageFormat)
    */
    DEVA_FRAMEWORK_API static Image loadImageFromFile(const std::string &filename, ImageFormat format);

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
	DEVA_FRAMEWORK_API const std::vector<byte_t>& getData() const;

	DEVA_FRAMEWORK_API ~Image();

protected:
	DEVA_FRAMEWORK_API virtual std::vector<byte_t> onRelease() override;
private:
	std::vector<byte_t> data;

};


}

#endif // DEVA_FRAMEWORK_GRAPHICS_IMAGE_H
