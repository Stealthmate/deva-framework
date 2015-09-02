file(GLOB_RECURSE SRCS ${CURDIR}/*.cpp ${CURDIR}/*.hpp)

add_library(deva-Math ${LIBTYPE} ${SRCS})
target_link_libraries(deva-Math deva-System)
set_property(TARGET deva-Math PROPERTY CXX_STANDARD 11)
target_link_libraries(deva-Math deva-System)
set_target_properties(deva-Math PROPERTIES COMPILE_DEFINITIONS DEVA_BUILD_MATH)
