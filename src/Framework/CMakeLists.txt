option(BUILD_SHARED_LIBS "Build the shared library" ON)
set(LIBTYPE STATIC)
if(BUILD_SHARED_LIBS)
set(DEVA_BUILD_DEFINES DEVA_BUILD_FRAMEWORK_SHARED)
set(LIBTYPE SHARED)
endif()

message("Generating DevaFramework build files...")

include(${CURDIR}/SourceList.cmake)
include(${CURDIR}/PublicHeaders.cmake)

set(DEVA_FRAMEWORK_LIB deva-Framework)
set(DEVA_FRAMEWORK_LIB_DEBUG ${DEVA_FRAMEWORK_LIB}${CMAKE_DEBUG_POSTFIX})

set(DEVA_FRAMEWORK_LINK_LIBRARIES ${DEVA_FRAMEWORK_LIB} ${DEVA_FRAMEWORK_DEP})
set(DEVA_FRAMEWORK_LINK_LIBRARIES_DEBUG ${DEVA_FRAMEWORK_LIB_DEBUG} ${DEVA_FRAMEWORK_DEP_DEBUG})

set(SRCS ${DEVA_FRAMEWORK_SOURCE_LIST})
set(PUBLIC_HEADERS ${DEVA_FRAMEWORK_PUBLIC_HEADERS})
add_library(${DEVA_FRAMEWORK_LIB} ${LIBTYPE} ${SRCS})

set_target_properties(${DEVA_FRAMEWORK_LIB} PROPERTIES COMPILE_DEFINITIONS ${DEVA_BUILD_DEFINES})
SET_LINK_LIBRARIES(${DEVA_FRAMEWORK_LIB} DEVA_FRAMEWORK_DEP_DEBUG DEVA_FRAMEWORK_DEP)

foreach(source IN LISTS SRCS)
    get_filename_component(source_path "${source}" ABSOLUTE)
    string(REGEX REPLACE ".*\/src\/Framework(.*)" "\\1" source_path "${source_path}")
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
