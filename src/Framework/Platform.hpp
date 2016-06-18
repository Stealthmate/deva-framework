#ifndef DEVA_FRAMEWORK_PLATFORM_H
#define DEVA_FRAMEWORK_PLATFORM_H

#ifdef _WIN32
#define DEVA_OS_WIN32
#else
#error "Platform not supported."
#endif

#endif //DEVA_FRAMEWORK_PLATFORM_H