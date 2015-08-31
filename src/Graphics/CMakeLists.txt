file(GLOB_RECURSE SRCS ${CURDIR}/*.cpp ${CURDIR}/*.hpp)

add_library(deva-Graphics ${LIBTYPE} ${SRCS})
set_property(TARGET deva-Graphics PROPERTY CXX_STANDARD 11)
target_link_libraries(deva-Graphics deva-System ${DEVA_FRAMEWORK_PROV_DEP_PNG} ${DEVA_FRAMEWORK_SYSTEM_DEP_OGL})
