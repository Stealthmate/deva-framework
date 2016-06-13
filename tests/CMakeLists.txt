set(TEST_LIST test-"")

add_executable(test-Window ${CURDIR}/Window.cpp)
add_dependencies(test-Window deva)
target_link_libraries(test-Window deva)
list(APPEND TEST_LIST test-Window)

add_executable(test-OpenGL ${CURDIR}/OpenGL.cpp)
add_dependencies(test-OpenGL deva)
target_link_libraries(test-OpenGL deva)
list(APPEND TEST_LIST test-OpenGL)

add_executable(test-Images ${CURDIR}/Images.cpp)
add_dependencies(test-Images deva)
target_link_libraries(test-Images deva)
list(APPEND TEST_LIST test-Images)

add_executable(test-RotatingCube ${CURDIR}/RotatingCube.cpp)
add_dependencies(test-RotatingCube deva)
target_link_libraries(test-RotatingCube deva)
list(APPEND TEST_LIST test-RotatingCube)

add_executable(test-FTText ${CURDIR}/FT_text.cpp)
add_dependencies(test-FTText deva)
target_link_libraries(test-FTText deva)
list(APPEND TEST_LIST test-FTText)

file(GLOB_RECURSE SRCS bin/shaders/*.glsl)
add_custom_target(Shaders ALL SOURCES ${SRCS})
