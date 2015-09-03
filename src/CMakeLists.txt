option(BUILD_SHARED_LIBS "Build the shared library" ON)
set(LIBTYPE STATIC)
if(BUILD_SHARED_LIBS)
add_definitions(-DDEVA_BUILD_SHARED)
set(LIBTYPE SHARED)
endif()

set(PRIVATE_HEADERS "")

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

set(GL_HEADER_DIR "../include/GL")
set(GLBINDING_HEADER_DIR "../include/glbinding")

set(CURDIR ${TEMP_DIR})
file(GLOB_RECURSE PUBLIC_HEADERS ${CURDIR}/*.hpp)
foreach(Header ${PUBLIC_HEADERS})
	foreach(privHeader ${PRIVATE_HEADERS})
		if(${Header} STREQUAL ${privHeader})
			list(REMOVE_ITEM PUBLIC_HEADERS privHeader)
		endif()
	endforeach(privHeader)
endforeach(Header)

set(PUBLIC_HEADER_OUTPUT_DIR ../public_headers/DevaFramework)

add_custom_target(PublicHeaders SOURCES ${PUBLIC_HEADERS})
foreach(Header ${PUBLIC_HEADERS})
	get_filename_component(DIRNAME ${Header} DIRECTORY)
	get_filename_component(DIRNAME ${DIRNAME} NAME)
	if(${DIRNAME} STREQUAL "src")
		set(DIRNAME ${PUBLIC_HEADER_OUTPUT_DIR})
	else()
		set(DIRNAME ${PUBLIC_HEADER_OUTPUT_DIR}/${DIRNAME})
	endif()
	add_custom_command(TARGET PublicHeaders COMMAND ${CMAKE_COMMAND} -E make_directory ${DIRNAME} COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${Header} ${DIRNAME})
endforeach()
add_custom_command(TARGET PublicHeaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${GL_HEADER_DIR} ${PUBLIC_HEADER_OUTPUT_DIR}/../GL)
add_custom_command(TARGET PublicHeaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLBINDING_HEADER_DIR} ${PUBLIC_HEADER_OUTPUT_DIR}/../glbinding)