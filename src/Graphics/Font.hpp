#ifndef DEVA_FRAMEWORK_GRAPHICS_FONT_H
#define DEVA_FRAMEWORK_GRAPHICS_FONT_H

#include "Config.hpp"

namespace DevaFramework 
{

	class Font 
	{
	public:
		static Font fromFile(const std::string &filename);

	private:
		

	public:
		Font();

		int stringWidth(const std::string &str);


	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_FONT_H