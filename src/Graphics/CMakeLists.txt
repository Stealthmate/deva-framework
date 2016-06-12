file(GLOB_RECURSE SRCS ${CURDIR}/*.cpp ${CURDIR}/*.hpp)

add_library(deva-Graphics ${LIBTYPE} ${SRCS})
set_property(TARGET deva-Graphics PROPERTY CXX_STANDARD 11)
target_link_libraries(deva-Graphics deva-System deva-Util ${DEVA_FRAMEWORK_PROV_DEP_FREETYPE} ${DEVA_FRAMEWORK_PROV_DEP_GLBINDING} ${DEVA_FRAMEWORK_PROV_DEP_PNG} ${DEVA_FRAMEWORK_SYSTEM_DEP_OGL})
set_target_properties(deva-Graphics PROPERTIES COMPILE_DEFINITIONS DEVA_BUILD_GRAPHICS)
list(APPEND PRIVATE_HEADERS ImageReaders.hpp)