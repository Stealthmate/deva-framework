#ifndef DEVA_FRAMEWORK_CONFIG_H
#define DEVA_FRAMEWORK_CONFIG_H

#ifdef _WIN32
	#ifdef DEVA_BUILD
		#ifdef DEVA_BUILD_SHARED
			#define DEVA_API __declspec(dllexport)
		#else
			#define DEVA_API
		#endif
	#else
		#define DEVA_API __declspec(dllimport)
	#endif
#endif

#define GLFW_DLL

#include <stdint.h>
#include <string>
#include <ostream>
#include <sstream>

namespace patch ///to_string doesn't work in MinGW
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#define strm(a) patch::to_string(a)

struct GLFWwindow;

///Encloses the whole Deva Framework and the functionality it provides
namespace DevaFramework
{

typedef GLFWwindow* Window_Handle;

typedef uint32_t ShaderID;
typedef uint32_t TextureID;
typedef short int Key;
typedef short int MouseButton;
}

#endif // DEVA_FRAMEWORK_CONFIG_H
