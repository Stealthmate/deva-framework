#ifndef DEVA_FRAMEWORK_SYSTEM_CONFIG_H
#define DEVA_FRAMEWORK_SYSTEM_CONFIG_H

#include "../Config.hpp"

#ifdef _MSC_VER
	#ifdef DEVA_BUILD_SHARED
		#ifdef DEVA_BUILD_SYSTEM
			#define DEVA_SYSTEM_API __declspec(dllexport)
		#else
			#define DEVA_SYSTEM_API __declspec(dllimport)
		#endif
	#else
		#define DEVA_SYSTEM_API __declspec(dllimport)
	#endif
	
#else
	#define DEVA_SYSTEM_API
#endif


namespace DevaFramework
{

}

#endif  //DEVA_FRAMEWORK_SYSTEM_CONFIG_H