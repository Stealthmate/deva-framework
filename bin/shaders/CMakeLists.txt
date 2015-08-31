file(GLOB_RECURSE SRCS ${CURDIR}/*.glsl)
add_custom_target(Shaders SOURCES ${SRCS})
