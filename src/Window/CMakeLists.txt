file(GLOB_RECURSE SRCS ${CURDIR}/*.cpp ${CURDIR}/*.hpp)

add_library(deva-Window ${LIBTYPE} ${SRCS})
set_property(TARGET deva-Window PROPERTY CXX_STANDARD 11)
target_link_libraries(deva-Window deva-System ${DEVA_FRAMEWORK_PROV_DEP_GLFW})