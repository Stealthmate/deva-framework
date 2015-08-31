file(GLOB_RECURSE SRCS ${CURDIR}/*.cpp ${CURDIR}/*.hpp)

add_library(deva-Util ${LIBTYPE} ${SRCS})
target_link_libraries(deva-Util deva-System)
set_property(TARGET deva-Util PROPERTY CXX_STANDARD 11)
