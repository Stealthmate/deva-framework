option(BUILD_SHARED_LIBS "Build the shared library" ON)
set(LIBTYPE STATIC)
if(BUILD_SHARED_LIBS)
set(DEVA_BUILD_DEFINES DEVA_ENGINE_BUILD_SHARED)
set(LIBTYPE SHARED)
endif()

message("Generating DevaEngine build files...")

include(${CURDIR}/CMakeSourceList.txt)

set(SRCS ${DEVA_ENGINE_SOURCE_LIST})
add_library(deva-Engine ${LIBTYPE} ${SRCS})

set_target_properties(deva-Engine PROPERTIES COMPILE_DEFINITIONS ${DEVA_BUILD_DEFINES})
target_link_libraries(deva-Engine deva-Framework ${DEVA_FRAMEWORK_DEP})
target_include_directories(deva-Engine PRIVATE ${DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR})

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

set(HEADER_OUTPUT_DIR ${DEVA_ENGINE_PUBLIC_INCLUDE_DIR}/)

foreach(header IN LISTS DEVA_ENGINE_PUBLIC_HEADERS)
	set(FORMATTED_PATH ${header})
	string(REPLACE "/" "\\" FORMATTED_PATH ${FORMATTED_PATH})

    string(REGEX REPLACE ".*\/Engine(.*)?\/.*" "${HEADER_OUTPUT_DIR}\/\\1\/" FORMATTED_OUTPUT_DIR "${header}")
	string(REGEX REPLACE "\/+" "\/" FORMATTED_OUTPUT_DIR ${FORMATTED_OUTPUT_DIR})
	string(REPLACE "/" "\\" FORMATTED_OUTPUT_DIR ${FORMATTED_OUTPUT_DIR})

    get_filename_component(FNAME ${header} NAME)
    add_custom_command(OUTPUT ${FORMATTED_OUTPUT_DIR}${FNAME}
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Copying public header ${header}..."
		COMMAND ${CMAKE_COMMAND} -E make_directory ${FORMATTED_OUTPUT_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${FORMATTED_PATH} ${FORMATTED_OUTPUT_DIR}
        MAIN_DEPENDENCY ${header})
endforeach()


set(GL_HEADER_DIR "../include/GL")
set(GLBINDING_HEADER_DIR "../include/glbinding")
