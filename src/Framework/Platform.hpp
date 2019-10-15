#ifndef DEVA_FRAMEWORK_PLATFORM_H
#define DEVA_FRAMEWORK_PLATFORM_H

#ifdef _WIN32
#define DEVA_OS_WIN32
#elif defined	__gnu_linux__
#define DEVA_OS_LINUX
#else
#error "Platform not supported."
#endif

#endif //DEVA_FRAMEWORK_PLATFORM_H
