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
#endif
#else
#define DEVA_ENGINE_API
#endif

#include <DevaFramework/Deva.hpp>

#endif // DEVA_ENGINE_CONFIG_H
