#include "Init.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../src/System/Logger.hpp"

using namespace DevaFramework;

namespace {
	int loadFreeType() {
		FT_Library ft;

		if (FT_Init_FreeType(&ft)) {
			Logger::err.println("Could not load FreeType.");
			return -1;
		}

		return 0;
	}
}
int DevaFramework::DEVA_INIT_GRAPHICS() {

	if (loadFreeType() != 0) return -1;

	return 0;
}