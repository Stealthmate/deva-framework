file(GLOB_RECURSE SRCS ${CURDIR}/*.cpp ${CURDIR}/*.hpp)

add_library(deva-System ${LIBTYPE} ${SRCS})
set_property(TARGET deva-System PROPERTY CXX_STANDARD 11)
