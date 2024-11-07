# project(civetweb)
# set(targetname libcivetweb)

set(CIVETWEB_SRC ${PROJECT_SOURCE_DIR}/src/civetweb)

set(CIVETWEB_INCLUDE ${CIVETWEB_SRC}/include)
set(CIVETWEB_LIB ${CIVETWEB_SRC}/lib/libcivetweb.a PARENT_SCOPE)

include_directories(${CIVETWEB_INCLUDE})
link_directories(${CIVETWEB_LIB})


#message(STATUS "civetweb include:${CIVETWEB_INCLUDE}, lib:${CIVETWEB_LIB}")