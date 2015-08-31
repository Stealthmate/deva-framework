option(BUILD_SHARED_LIBS "Build the shared library" ON)
add_definitions(-DDEVA_BUILD)
set(LIBTYPE STATIC)
if(BUILD_SHARED_LIBS)
add_definitions(-DDEVA_BUILD_SHARED)
set(LIBTYPE SHARED)
endif()

add_custom_target(Config SOURCES ${CURDIR}/Config.hpp ${CURDIR}/CMakeLists.txt)
set(TEMP_DIR ${CURDIR})
#System
set(CURDIR ${TEMP_DIR}/System)
include(${CURDIR}/CMakeLists.txt)
#Window
set(CURDIR ${TEMP_DIR}/Window)
include(${CURDIR}/CMakeLists.txt)
#Graphics
set(CURDIR ${TEMP_DIR}/Graphics)
include(${CURDIR}/CMakeLists.txt)
#Math
set(CURDIR ${TEMP_DIR}/Math)
include(${CURDIR}/CMakeLists.txt)
#Util
set(CURDIR ${TEMP_DIR}/Util)
include(${CURDIR}/CMakeLists.txt)