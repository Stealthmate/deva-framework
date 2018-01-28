#ifndef DEVA_FRAMEWORK_GRAPHICS_IMAGE_H
#define DEVA_FRAMEWORK_GRAPHICS_IMAGE_H

#include "Config.hpp"

namespace DevaFramework
{

	struct Image
	{
		const ImageFormat format;
		const unsigned int width;
		const unsigned int height;
		const std::vector<byte_t> data;

		DEVA_FRAMEWORK_API Image(std::vector<byte_t> data, size_t width, size_t height, ImageFormat format);
	};

	/** Create an Image object from a file, treating it as a specified format
	@param filename The name of the file, the image is stored in
	@param format The format of the image
	*/
	DEVA_FRAMEWORK_API Image readImagePNG(std::istream &source);
}

#endif // DEVA_FRAMEWORK_GRAPHICS_IMAGE_H
