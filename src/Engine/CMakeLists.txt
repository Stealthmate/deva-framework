option(BUILD_SHARED_LIBS "Build the shared library" ON)
set(LIBTYPE STATIC)
if(BUILD_SHARED_LIBS)
set(DEVA_BUILD_DEFINES DEVA_ENGINE_BUILD_SHARED)
set(LIBTYPE SHARED)
endif()

message("Generating DevaEngine build files...")

include(${CURDIR}/SourceList.cmake)
include(${CURDIR}/PublicHeaders.cmake)

set(DEVA_ENGINE_LIB deva-Engine)
set(DEVA_ENGINE_LIB_DEBUG ${DEVA_ENGINE_LIB}${CMAKE_DEBUG_POSTFIX})

set(DEVA_ENGINE_LINK_LIBRARIES ${DEVA_ENGINE_LIB} ${DEVA_FRAMEWORK_LINK_LIBRARIES})
set(DEVA_ENGINE_LINK_LIBRARIES_DEBUG ${DEVA_ENGINE_LIB_DEBUG} ${DEVA_FRAMEWORK_LINK_LIBRARIES_DEBUG})

set(SRCS ${DEVA_ENGINE_SOURCE_LIST})
add_library(${DEVA_ENGINE_LIB} ${LIBTYPE} ${SRCS})
add_dependencies(${DEVA_ENGINE_LIB} ${DEVA_FRAMEWORK_LIB})

set_target_properties(${DEVA_ENGINE_LIB} PROPERTIES COMPILE_DEFINITIONS ${DEVA_BUILD_DEFINES})
SET_LINK_LIBRARIES(${DEVA_ENGINE_LIB} DEVA_FRAMEWORK_LINK_LIBRARIES_DEBUG DEVA_FRAMEWORK_LINK_LIBRARIES)

target_include_directories(${DEVA_ENGINE_LIB} PRIVATE ${DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR})

foreach(source IN LISTS SRCS)
    get_filename_component(source_path "${source}" ABSOLUTE)
    string(REGEX REPLACE ".*\/src\/Engine(.*)" "\\1" source_path "${source_path}")
    string(REGEX REPLACE "(.*\/.*(hpp|inl))" "Headers\/\\1" source_path "${source_path}")
	string(REGEX REPLACE "(.*\/.*cpp)" "Source Files\/\\1" source_path "${source_path}")
	string(REGEX REPLACE "/[0-9a-zA-Z_\-]*\.(cpp|hpp|inl)" "" source_path "${source_path}")
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
	if(source_path_msvc)
		source_group("${source_path_msvc}" FILES "${source}")
	endif()
endforeach()


set(GL_HEADER_DIR "../include/GL")
set(GLBINDING_HEADER_DIR "../include/glbinding")
