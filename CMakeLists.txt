#Deva
#Version 1.0

project(Deva)
cmake_minimum_required(VERSION 3.2.2)

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
set(DEVA_VERSION 0.2)
add_definitions(-DDEVA_VERSION=${DEVA_VERSION})

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
set(DEVA_FRAMEWORK_PROV_DEP_PNG libpng16)
set(DEVA_FRAMEWORK_PROV_DEP_FREETYPE freetype263)

#All dependencies
set(
	DEVA_FRAMEWORK_DEP 
	${DEVA_FRAMEWORK_PROV_DEP_VULKAN}
	${DEVA_FRAMEWORK_SYSTEM_DEP_OGL} 
	${DEVA_FRAMEWORK_PROV_DEP_GLBINDING}
	# ${DEVA_FRAMEWORK_PROV_DEP_GLFW} 
	${DEVA_FRAMEWORK_PROV_DEP_PNG} 
	#${DEVA_FRAMEWORK_PROV_DEP_LUA} 
	${DEVA_FRAMEWORK_PROV_DEP_FREETYPE}
)


set(SHADERS_OUTPUT_DIR bin/shaders)

set(DEVA_MASTER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#Framework Sources
set(CURDIR ${DEVA_MASTER_DIR}/Framework)
set(DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR ${DEVA_MASTER_DIR}/framework_include/DevaFramework)
set(DEVA_ENGINE_PUBLIC_INCLUDE_DIR ${DEVA_MASTER_DIR}/engine_include/DevaEngine)
include(${CURDIR}/CMakeLists.txt)
set(DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR ${DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR}/../)

#Engine Sources
set(CURDIR ${DEVA_MASTER_DIR}/Engine)
include(${CURDIR}/CMakeLists.txt)
set(DEVA_ENGINE_PUBLIC_INCLUDE_DIR ${DEVA_ENGINE_PUBLIC_INCLUDE_DIR}/../)

set(DEVA_ENGINE_LINK_LIBRARIES deva-Engine deva-Framework ${DEVA_FRAMEWORK_PROV_DEP})

#Tests
set(CURDIR tests)
include(${CURDIR}/CMakeLists.txt)
#Docs
set(DOXYFILE_NAME "DevaFramework.doxy")
add_custom_target(Docs COMMAND cd .. && doxygen DevaFramework.doxy)