#ifndef DEVA_ENGINE_CONFIG_H
#define DEVA_ENGINE_CONFIG_H

#define GLFW_DLL

#include <stdint.h>
#include <string>

#ifdef _MSC_VER
#ifdef DEVA_BUILD_SHARED
#define DEVA_ENGINE_API __declspec(dllexport)
#else
#define DEVA_ENGINE_API __declspec(dllimport)

#ifndef DEVA_ENGINE_MASTER_H
#error "DO NOT INCLUDE THESE HEADERS MANUALLY! USE Deva.hpp INSTEAD!"
#endif
#endif
#include <ostream>
#include <sstream>
namespace patch ///to_string doesn't work in MinGW
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}
#define strm(a) patch::to_string(a)
#else
#define strm(a) std::to_string(a)
#define DEVA_ENGINE_API
#endif

#include "Platform.hpp"

///Encloses the whole Deva Framework and the functionality it provides
namespace DevaFramework
{
	typedef uint32_t ShaderID;
	typedef uint32_t TextureID;

	typedef uint8_t byte_t;
}


#ifdef DEVA_DEBUG
#endif

#endif // DEVA_ENGINE_CONFIG_H