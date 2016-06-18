option(BUILD_SHARED_LIBS "Build the shared library" ON)
set(LIBTYPE STATIC)
if(BUILD_SHARED_LIBS)
set(DEVA_BUILD_DEFINES DEVA_BUILD_SHARED)
set(LIBTYPE SHARED)
endif()

include(${CURDIR}/CMakeSourceList.txt)

set(SRCS ${DEVA_FRAMEWORK_SOURCE_LIST})
add_library(deva-Framework ${LIBTYPE} ${SRCS})

set_target_properties(deva-Framework PROPERTIES COMPILE_DEFINITIONS ${DEVA_BUILD_DEFINES})
target_link_libraries(deva-Framework ${DEVA_FRAMEWORK_DEP})

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

add_custom_command(TARGET deva-Framework 
	COMMAND ${CMAKE_COMMAND} -E copy ${DEVA_FRAMEWORK_PUBLIC_HEADERS} ${DEVA_ENGINE_INLCUDE_DIR})

set(GL_HEADER_DIR "../include/GL")
set(GLBINDING_HEADER_DIR "../include/glbinding")