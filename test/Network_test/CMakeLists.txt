project(network_test)

add_executable(
    ${PROJECT_NAME}
    Network_test.cpp
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    libcommon
    libnetworks
    ${CIVETWEB_LIB}
)

message(STATUS "CivetWeb Library Path: ${CMAKE_BINARY_DIR}/libcivetweb.a")
  
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)




