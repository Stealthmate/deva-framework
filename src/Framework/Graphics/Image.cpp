#include "Image.hpp"

#include<libpng\png.h>

using namespace DevaFramework;

namespace {

	static void readData(png_structp pngPtr, png_bytep data, png_size_t length)
	{
		png_voidp a = png_get_io_ptr(pngPtr);
		((std::istream*)a)->read((char*)data, length);
	}

	ImageFormat chooseFormat(png_uint_32 colorType) {
		switch (colorType) {
		case PNG_COLOR_TYPE_GRAY: 
			return ImageFormat::R8_UNORM;
		case PNG_COLOR_TYPE_GA: 
			return ImageFormat::R8G8_UNORM;
		case PNG_COLOR_TYPE_PALETTE:
		case PNG_COLOR_TYPE_RGB:
			return ImageFormat::R8G8B8_UNORM;
		case PNG_COLOR_TYPE_RGBA:
			return ImageFormat::R8G8B8A8_UNORM;
		}
	}
}

Image DevaFramework::readImagePNG(std::istream &source) {

	png_byte png_signature[8];
	int is_not_png = 0;
	source.read((char*)png_signature, 8);

	is_not_png = png_sig_cmp(png_signature, 0, 8);
	if (is_not_png)
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
	std::vector<byte_t> data;
	png_set_read_fn(pngPtr, (png_voidp)&source, readData);
	png_set_sig_bytes(pngPtr, 8);
	png_read_info(pngPtr, infoPtr);

	png_uint_32 imgWidth = png_get_image_width(pngPtr, infoPtr);
	png_uint_32 imgHeight = png_get_image_height(pngPtr, infoPtr);
	png_uint_32 bitdepth = png_get_bit_depth(pngPtr, infoPtr);
	png_uint_32 channels = png_get_channels(pngPtr, infoPtr);
	png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);

	rowPtrs = new png_bytep[imgHeight];

	size_t data_size = imgWidth * imgHeight * bitdepth * channels / 8;
	data = std::vector<byte_t>(data_size);
	data.resize(data_size);

	size_t stride = data_size / imgHeight;

	for (size_t i = 0; i < imgHeight; i++)
	{
		png_uint_32 q = (png_uint_32)((imgHeight - i - 1) * stride);
		rowPtrs[i] = (png_bytep)data.data() + q;
	}
	
	png_set_expand(pngPtr);
	if(bitdepth > 8) png_set_strip_16(pngPtr);

	png_read_image(pngPtr, rowPtrs);

	delete[] rowPtrs;
	png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);

	return Image(data, imgWidth, imgHeight, chooseFormat(color_type));
}


Image::Image(std::vector<byte_t> data, size_t width, size_t height, ImageFormat format)
	: data(std::move(data)), width(width), height(height), format(format) {}