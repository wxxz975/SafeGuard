project(inference_test)

find_package(OpenCV REQUIRED)

add_executable(
    ${PROJECT_NAME}
    Inference_test.cpp
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    ${OpenCV_LIBS}
    libcommon
    libinference
)


set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)




