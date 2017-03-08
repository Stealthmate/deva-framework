#Deva
#Version 1.0

project(Deva)
cmake_minimum_required(VERSION 3.2.2)

option(BUILD_OPENGL "Build with support for OpenGL" OFF)
option(BUILD_VULKAN "Build with support for Vulkan" ON)

set(BINDIR ../bin)
set(LIBDIR ../bin/lib)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINDIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBDIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBDIR} )

foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BINDIR} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBDIR} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBDIR} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

#Version
set(DevaFramework_VERSION_MAJOR 1)
set(DevaFramework_VERSION_MINOR 0)

#Set include path
include_directories("include/")
link_directories("lib/" "bin/lib")
set(DEVA_VERSION_MAJOR 0)
set(DEVA_VERSION_MINOR 1)
set(DEVA_VERSION_PATCH 0)
add_definitions(-DDEVA_VERSION_MACRO_MAJOR=${DEVA_VERSION_MAJOR})
add_definitions(-DDEVA_VERSION_MACRO_MINOR=${DEVA_VERSION_MINOR})
add_definitions(-DDEVA_VERSION_MACRO_PATCH=${DEVA_VERSION_PATCH})

if(${BUILD_OPENGL})
	message("Building with support for OpenGL")
	add_definitions(-DDEVA_BUILD_OPENGL)
endif()
if(${BUILD_VULKAN})
	message("Building with support for Vulkan")
	add_definitions(-DDEVA_BUILD_VULKAN)
endif()

set(REQUIRED_COMPILER_VERSION_GCC "4.8")
set(REQUIRED_COMPILER_VERSION_MSVC "19.0")

set(COMPILER ${CMAKE_CXX_COMPILER_ID})

if (${COMPILER} STREQUAL "Clang")
  # using Clang
elseif (${COMPILER} STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
		message( SEND_ERROR "Compiler version is lower than required (${REQUIRED_COMPILER_VERSION_GCC})! Build may fail!")
	else()
		SET( CMAKE_CXX_FLAGS  "-Wall -std=c++14" )
	endif()
elseif (${COMPILER} STREQUAL "Intel")
  # using Intel C++

elseif (${COMPILER} STREQUAL MSVC) # For some reason CMake complains about dereferencing MSVC when it's a string
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${REQUIRED_COMPILER_VERSION_MSVC})
		message( SEND_ERROR "Compiler version is lower than required (${REQUIRED_COMPILER_VERSION_MSVC})! Build may fail!")
	endif()
	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4251" )
endif()

#System dependencies
if (WIN32)
set(DEVA_FRAMEWORK_SYSTEM_DEP_OGL opengl32 glu32)
else()
set(DEVA_FRAMEWORK_SYSTEM_DEP_OGL GLU glbinding GL X11 Xxf86vm Xrandr pthread Xi Xinerama Xcursor)
endif()

#Provided dependencies
set(DEVA_FRAMEWORK_PROV_DEP_VULKAN vulkan-1)
set(DEVA_FRAMEWORK_PROV_DEP_GLBINDING glbinding)
set(DEVA_FRAMEWORK_PROV_DEP_GLFW glfw3)
set(DEVA_FRAMEWORK_PROV_DEP_LUA lua)
set(DEVA_FRAMEWORK_PROV_DEP_FMT fmt)
set(DEVA_FRAMEWORK_PROV_DEP_PNG libpng16)
set(DEVA_FRAMEWORK_PROV_DEP_FREETYPE freetype263)
set(DEVA_FRAMEWORK_PROV_DEP_GTEST gtestd)

#All dependencies
set(
	DEVA_FRAMEWORK_DEP
	${DEVA_FRAMEWORK_PROV_DEP_VULKAN}
	${DEVA_FRAMEWORK_SYSTEM_DEP_OGL}
	${DEVA_FRAMEWORK_PROV_DEP_GLBINDING}
	# ${DEVA_FRAMEWORK_PROV_DEP_GLFW}
	${DEVA_FRAMEWORK_PROV_DEP_PNG}
	${DEVA_FRAMEWORK_PROV_DEP_LUA}
	${DEVA_FRAMEWORK_PROV_DEP_FMT}
	${DEVA_FRAMEWORK_PROV_DEP_FREETYPE}
    ${DEVA_FRAMEWORK_PROV_DEP_GTEST}
)


set(SHADERS_OUTPUT_DIR bin/shaders)

set(DEVA_MASTER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#Framework Sources
set(CURDIR ${DEVA_MASTER_DIR}/Framework)
set(DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR ${DEVA_MASTER_DIR}/framework_include/DevaFramework)
set(DEVA_ENGINE_PUBLIC_INCLUDE_DIR ${DEVA_MASTER_DIR}/engine_include/DevaEngine)
include(${CURDIR}/CMakeLists.txt)

#Framework Public Headers
set(HEADER_OUTPUT_DIR ${DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR}/)
add_custom_target(PublicHeaders DEPENDS ${DEVA_FRAMEWORK_PUBLIC_HEADERS})
foreach(header IN LISTS DEVA_FRAMEWORK_PUBLIC_HEADERS)
	set(FORMATTED_PATH ${header})
	string(REPLACE "/" "\\" FORMATTED_PATH ${FORMATTED_PATH})

    string(REGEX REPLACE ".*\/Framework(.*)?\/.*" "${HEADER_OUTPUT_DIR}\/\\1\/" FORMATTED_OUTPUT_DIR "${header}")
	string(REGEX REPLACE "\/+" "\/" FORMATTED_OUTPUT_DIR ${FORMATTED_OUTPUT_DIR})
	string(REPLACE "/" "\\" FORMATTED_OUTPUT_DIR ${FORMATTED_OUTPUT_DIR})

    get_filename_component(FNAME ${header} NAME)
	add_custom_command(TARGET PublicHeaders
		COMMAND ${CMAKE_COMMAND} -E make_directory ${FORMATTED_OUTPUT_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${FORMATTED_PATH} ${FORMATTED_OUTPUT_DIR}
        DEPENDS ${header})
endforeach()
set(DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR ${DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR}/../)

#Engine Sources
set(CURDIR ${DEVA_MASTER_DIR}/Engine)
include(${CURDIR}/CMakeLists.txt)

set(DEVA_FRAMEWORK_LINK_LIBRARIES deva-Framework ${DEVA_FRAMEWORK_DEP})
set(DEVA_ENGINE_LINK_LIBRARIES deva-Engine ${DEVA_FRAMEWORK_LINK_LIBRARIES})

#Engine Public Headers
set(HEADER_OUTPUT_DIR ${DEVA_ENGINE_PUBLIC_INCLUDE_DIR}/)
foreach(header IN LISTS DEVA_ENGINE_PUBLIC_HEADERS)
	set(FORMATTED_PATH ${header})
	string(REPLACE "/" "\\" FORMATTED_PATH ${FORMATTED_PATH})

    string(REGEX REPLACE ".*\/Engine(.*)?\/.*" "${HEADER_OUTPUT_DIR}\/\\1\/" FORMATTED_OUTPUT_DIR "${header}")
	string(REGEX REPLACE "\/+" "\/" FORMATTED_OUTPUT_DIR ${FORMATTED_OUTPUT_DIR})
	string(REPLACE "/" "\\" FORMATTED_OUTPUT_DIR ${FORMATTED_OUTPUT_DIR})

    get_filename_component(FNAME ${header} NAME)
	add_custom_command(TARGET PublicHeaders
		COMMAND ${CMAKE_COMMAND} -E make_directory ${FORMATTED_OUTPUT_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${FORMATTED_PATH} ${FORMATTED_OUTPUT_DIR}
        DEPENDS ${header})
endforeach()
set(DEVA_ENGINE_PUBLIC_INCLUDE_DIR ${DEVA_ENGINE_PUBLIC_INCLUDE_DIR}/../)

#Tests
set(CURDIR tests)
include(${CURDIR}/CMakeLists.txt)
#Docs
set(DOXYFILE_NAME "DevaFramework.doxy")
add_custom_target(Docs COMMAND cd .. && doxygen DevaFramework.doxy)
