#ifndef DEVA_FRAMEWORK_CONFIG_H
#define DEVA_FRAMEWORK_CONFIG_H

#define GLFW_DLL

#include <stdint.h>
#include <string>

#ifdef _MSC_VER
	#ifdef DEVA_BUILD_FRAMEWORK_SHARED
		#define DEVA_FRAMEWORK_API __declspec(dllexport)
	#else
		#define DEVA_FRAMEWORK_API __declspec(dllimport)
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
	#define DEVA_FRAMEWORK_API
#endif

#include "Platform.hpp"

///Encloses the whole Deva Framework and the functionality it provides
namespace DevaFramework
{
	typedef uint32_t ShaderID;
	typedef uint32_t TextureID;

	typedef uint8_t byte_t;

	const uint32_t DEVA_VERSION_MAJOR = DEVA_VERSION_MACRO_MAJOR;
	const uint32_t DEVA_VERSION_MINOR = DEVA_VERSION_MACRO_MINOR;
	const uint32_t DEVA_VERSION_PATCH = DEVA_VERSION_MACRO_PATCH;
}

#ifdef DEVA_DEBUG
#include "DevaLogger.hpp"
#endif



#endif // DEVA_FRAMEWORK_CONFIG_H
