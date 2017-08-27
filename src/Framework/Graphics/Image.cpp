#include "Image.hpp"

#include "ImageReaders.hpp"

#include <string>

using namespace DevaFramework;

Image Image::loadImageFromFile(const std::string &filename, ImageFormat format)
{
	RawImage raw;

	switch (format)
	{
	case PNG:
	{
		raw = readPNG(filename);
	}
	break;
	}

	if (raw.error)
	{
		LOG.e("Could not load image. Error code: " + strm(raw.error));
		return Image();
	}

	Image img;
	img.width = raw.width;
	img.height = raw.height;

	if (raw.color_type == COLOR_TYPE_RGBA && raw.bitdepth == 8)
	{
		img.data = std::move(raw.data);
		return img;
	}
	else if (raw.bitdepth == 8)
	{
		std::vector<byte_t> new_data(raw.width*raw.height*DEVA_IMAGE_BITS_PER_PIXEL);
		for (unsigned int i = 0;i <= raw.height - 1;i++)
		{
			for (unsigned int j = 0;j < raw.width - 1;j++)
			{
				new_data[(4 * i*raw.width) + (4 * j) + 0] = raw.data[(raw.channels*i*raw.width) + (raw.channels*j) + 0];
				new_data[(4 * i*raw.width) + (4 * j) + 1] = raw.data[(raw.channels*i*raw.width) + (raw.channels*j) + 1];
				new_data[(4 * i*raw.width) + (4 * j) + 2] = raw.data[(raw.channels*i*raw.width) + (raw.channels*j) + 2];
				new_data[(4 * i*raw.width) + (4 * j) + 3] = (byte_t) 0xFF;

			}
		}

		img.data = std::move(new_data);

		return img;
	}
	else return Image();
}

Image::Image()
{
	this->width = 0;
	this->height = 0;
}

Image::Image(const Image &img) = default;

Image::Image(Image &&img) = default;

Image& Image::operator=(const Image& img) = default;

Image& Image::operator=(Image &&img) = default;

const std::vector<byte_t>& Image::getData() const {
	return this->data;
}

std::vector<byte_t> Image::onRelease() {
	return std::move(data);
}

Image::~Image() = default;
