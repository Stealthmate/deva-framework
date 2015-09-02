set(TEST_LIST "")

add_executable(Window ${CURDIR}/Window.cpp)
add_dependencies(Window deva-Window)
target_link_libraries(Window deva-Window)
list(APPEND TEST_LIST Window)

add_executable(OpenGL ${CURDIR}/OpenGL.cpp)
add_dependencies(OpenGL deva-Window deva-Graphics deva-Util)
target_link_libraries(OpenGL deva-Window deva-Graphics deva-Util deva-Math ${DEVA_FRAMEWORK_SYSTEM_DEP_OGL})
list(APPEND TEST_LIST OpenGL)

add_executable(Images ${CURDIR}/Images.cpp)
add_dependencies(Images deva-Window deva-Graphics)
target_link_libraries(Images deva-Window deva-Graphics deva-Util)
list(APPEND TEST_LIST Images)

add_executable(RotatingCube ${CURDIR}/RotatingCube.cpp)
add_dependencies(RotatingCube deva-Window deva-Graphics deva-Util)
target_link_libraries(RotatingCube deva-Window deva-Graphics deva-Util deva-Math ${DEVA_FRAMEWORK_SYSTEM_DEP_OGL})
list(APPEND TEST_LIST RotatingCube)

file(GLOB_RECURSE SRCS bin/shaders/*.glsl)
add_custom_target(Shaders ALL SOURCES ${SRCS})
