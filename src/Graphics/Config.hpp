#ifndef DEVA_FRAMEWORK_GRAPHICS_CONFIG_H
#define DEVA_FRAMEWORK_GRAPHICS_CONFIG_H

#include "../Config.hpp"

#ifdef _MSC_VER
	#ifdef DEVA_BUILD_GRAPHICS
		#ifdef DEVA_BUILD_SHARED
			#define DEVA_GRAPHICS_API __declspec(dllexport)
		#else
			#define DEVA_GRAPHICS_API __declspec(dllimport)
		#endif
	#else
		#define DEVA_GRAPHICS_API
	#endif
#endif

namespace DevaFramework
{
	///The number of bits per pixel used in all internal representations of an image
	const unsigned int DEVA_IMAGE_BITS_PER_PIXEL = 32;
	///The number of channels used in all internal representations of an image
	const unsigned int DEVA_IMAGE_CHANNELS = 4;
	///The number of bits per channel used in all internal representations of an image
	const unsigned int DEVA_IMAGE_BITS_PER_CHANNEL = 8;

	///A color type with a single channel - Luminosity (GrayScale)
	const unsigned int COLOR_TYPE_GS = 0;
	///A color type with 3 channels - Red, Green, Blue
	const unsigned int COLOR_TYPE_RGB = 2;
	///A color type with 2 channels - Luminosity (GrayScale) and Alpha
	const unsigned int COLOR_TYPE_GSA = 4;
	///A color type with 4 channels - Red, Green, Blue and Alpha
	const unsigned int COLOR_TYPE_RGBA = 6;


	///A collection of supported ImageFormats
	enum ImageFormat
	{
		PNG = 0x00
	};

}

#endif // DEVA_FRAMEWORK_GRAPHICS_CONFIG_H
