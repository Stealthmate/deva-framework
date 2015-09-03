#include "Image.hpp"

#include "ImageReaders.hpp"
#include "../System/Logger.hpp"

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
		Logger::err << Logger::err.stamp << "Could not load image. Error code: " << raw.error << Logger::endl;
		return Image();
	}

	Image img;
	img.width = raw.width;
	img.height = raw.height;

	if (raw.color_type == COLOR_TYPE_RGBA && raw.bitdepth == 8)
	{
		img.data = raw.data;
		return img;
	}
	else if (raw.bitdepth == 8)
	{
		unsigned char* new_data = new unsigned char[raw.width*raw.height*DEVA_IMAGE_BITS_PER_PIXEL];
		Logger::warn << (int)raw.channels;
		for (int i = 0;i <= raw.height - 1;i++)
		{
			for (auto j = 0;j < raw.width - 1;j++)
			{
				new_data[(4 * i*raw.width) + (4 * j) + 0] = raw.data[(raw.channels*i*raw.width) + (raw.channels*j) + 0];
				new_data[(4 * i*raw.width) + (4 * j) + 1] = raw.data[(raw.channels*i*raw.width) + (raw.channels*j) + 1];
				new_data[(4 * i*raw.width) + (4 * j) + 2] = raw.data[(raw.channels*i*raw.width) + (raw.channels*j) + 2];
				new_data[(4 * i*raw.width) + (4 * j) + 3] = 0xFF;

			}
		}

		img.data = new_data;
		delete raw.data;

		return img;
	}
	else return Image();
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

	this->data = new unsigned char[image_size];

	for (auto i = 0; i < image_size; i++) this->data[i] = img.data[i];
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

	if (!this->data) delete[] this->data;

	this->data = new unsigned char[image_size];

	for (int i = 0; i < image_size; i++) this->data[i] = img.data[i];

	return *this;
}

Image& Image::operator=(Image &&img)
{
	this->width = img.width;
	this->height = img.height;
	unsigned long int image_size = width * height * DEVA_IMAGE_BITS_PER_PIXEL / 8;

	if (!this->data) delete[] this->data;

	this->data = img.data;

	img.data = 0;
	return *this;
}

unsigned char * const Image::getData() const {
	return this->data;
}

Image::~Image()
{
	if (this->data) delete[] this->data;
}
