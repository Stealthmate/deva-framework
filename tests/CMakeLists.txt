set(TEST_LIST "")
set(TEST_SRC_LIST "")

function(add_approval_test name)
	set(__OPTIONAL_SRCS ${ARGN})

	set(TEMP_DIR ${CURDIR})
	set(CURDIR ${TEMP_DIR}/${name})

	if(__OPTIONAL_SRCS)
		string(REGEX REPLACE "([^;]+;?)" "${CURDIR}\/\\1" __OPTIONAL_SRCS "${__OPTIONAL_SRCS}")
	endif()

	add_executable(test-${name} ${CURDIR}/test-${name}.cpp ${__OPTIONAL_SRCS})
	target_link_libraries(test-${name} ${DEVA_ENGINE_LINK_LIBRARIES})
	target_include_directories(test-${name} PUBLIC ${DEVA_ENGINE_PUBLIC_INCLUDE_DIR} ${DEVA_FRAMEWORK_PUBLIC_INCLUDE_DIR})

	set(TEST_LIST ${TEST_LIST} test-${name} PARENT_SCOPE)
	set(TEST_SRC_LIST ${TEST_SRC_LIST} ${CURDIR}/test-${name}.cpp ${__OPTIONAL_SRCS} PARENT_SCOPE)
endfunction()

function(target_copy_files target dest files)

	set(__FILES ${files} ${ARGN})
	string(REGEX REPLACE "(.+)" "../${CURDIR}\/${target}\/\\1" __FILES "${__FILES}")
	message(${__FILES})
	message(${dest})
	add_custom_command(TARGET test-${target}
		COMMAND ${CMAKE_COMMAND} -E make_directory ${dest}
		message(${dest})
		COMMAND ${CMAKE_COMMAND} -E copy ${__FILES} ${dest})
endfunction()

add_approval_test(Window)
# add_approval_test(OpenGL "VertexShader.inl" "FragmentShader.inl")
# add_approval_test(Images "VertexShader.inl" "FragmentShader.inl")
# target_copy_files(Images ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources SS1.png)
# add_approval_test(RotatingCube "VertexShader.inl" "FragmentShader.inl")
add_approval_test(Vulkan)
# add_approval_test("Model")
# add_approval_test("FT_text")

add_custom_target(test-all)
add_dependencies(test-all ${TEST_LIST})
foreach(source IN LISTS TEST_SRC_LIST)
    get_filename_component(source_path "${source}" ABSOLUTE)
    string(REGEX REPLACE ".*\/tests(.*)" "\\1" source_path "${source_path}")
	string(REGEX REPLACE "/[^\/]*$" "" source_path "${source_path}")
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
	if(source_path_msvc)
		source_group("${source_path_msvc}" FILES "${source}")
	endif()
endforeach()

file(GLOB MY_PUBLIC_HEADERS
  "myDir/*.h"
)
file(COPY ${MY_PUBLIC_HEADERS} DESTINATION myDestination)

file(GLOB_RECURSE SRCS bin/shaders/*.glsl)
add_custom_target(Shaders ALL SOURCES ${SRCS})
