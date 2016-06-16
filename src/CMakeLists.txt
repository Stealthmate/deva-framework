option(BUILD_SHARED_LIBS "Build the shared library" ON)
set(LIBTYPE STATIC)
if(BUILD_SHARED_LIBS)
set(DEVA_BUILD_DEFINES DEVA_BUILD_SHARED)
set(LIBTYPE SHARED)
endif()

set(PRIVATE_HEADERS "")

set(DEVA_SOURCE_LIST "")

set( 
	DEVA_SOURCE_LIST 
	${DEVA_SOURCE_LIST} 
	${CURDIR}/Config.hpp
	${CURDIR}/Deva.hpp
	${CURDIR}/Deva.cpp
)

include(${CURDIR}/CMakeSourceList.txt)

set(SRCS ${DEVA_SOURCE_LIST})
add_library(deva ${LIBTYPE} ${SRCS})

set_target_properties(deva PROPERTIES COMPILE_DEFINITIONS ${DEVA_BUILD_DEFINES})
target_link_libraries(deva ${DEVA_FRAMEWORK_DEP})

foreach(source IN LISTS SRCS)
    get_filename_component(source_path "${source}" ABSOLUTE)
    string(REGEX REPLACE ".*\/src(.*)" "\\1" source_path "${source_path}")
    string(REGEX REPLACE "(.*\/*.(hpp|inl))" "Headers\/\\1" source_path "${source_path}")
	string(REGEX REPLACE "(.*\/*.cpp)" "Source Files\/\\1" source_path "${source_path}")
	string(REGEX REPLACE "/[a-zA-Z\-]*.(cpp|hpp|inl)" "" source_path "${source_path}")
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
	if(source_path_msvc)
		source_group("${source_path_msvc}" FILES "${source}")
	endif()
endforeach()


set(GL_HEADER_DIR "../include/GL")
set(GLBINDING_HEADER_DIR "../include/glbinding")

# set(CURDIR ${TEMP_DIR})
# file(GLOB_RECURSE PUBLIC_HEADERS ${CURDIR}/*.hpp)
# foreach(Header ${PUBLIC_HEADERS})
	# foreach(privHeader ${PRIVATE_HEADERS})
		# if(${Header} STREQUAL ${privHeader})
			# list(REMOVE_ITEM PUBLIC_HEADERS privHeader)
		# endif()
	# endforeach(privHeader)
# endforeach(Header)

# set(PUBLIC_HEADER_OUTPUT_DIR ../public_headers/DevaFramework)

# add_custom_target(PublicHeaders SOURCES ${PUBLIC_HEADERS})
# foreach(Header ${PUBLIC_HEADERS})
	# get_filename_component(DIRNAME ${Header} DIRECTORY)
	# get_filename_component(DIRNAME ${DIRNAME} NAME)
	# if(${DIRNAME} STREQUAL "src")
		# set(DIRNAME ${PUBLIC_HEADER_OUTPUT_DIR})
	# else()
		# set(DIRNAME ${PUBLIC_HEADER_OUTPUT_DIR}/${DIRNAME})
	# endif()
	# add_custom_command(TARGET PublicHeaders COMMAND ${CMAKE_COMMAND} -E make_directory ${DIRNAME} COMMAND ${CMAKE_COMMAND}
    # ARGS -E copy ${Header} ${DIRNAME})
# endforeach()
# add_custom_command(TARGET PublicHeaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${GL_HEADER_DIR} ${PUBLIC_HEADER_OUTPUT_DIR}/../GL)
# add_custom_command(TARGET PublicHeaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLBINDING_HEADER_DIR} ${PUBLIC_HEADER_OUTPUT_DIR}/../glbinding)