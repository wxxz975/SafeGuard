# top 
cmake_minimum_required(VERSION 3.22)
project(SafeGuard)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



find_package(nlohmann_json REQUIRED)

add_subdirectory(externals)
add_subdirectory(src)

# add_subdirectory(src/Common)
# add_subdirectory(src/Communications)
# add_subdirectory(src/Inference)
# add_subdirectory(src/XRayDetection)

# add_executable(
#     ${CMAKE_PROJECT_NAME}
#     ${CMAKE_SOURCE_DIR}/src/main.cpp
# )

# target_link_libraries(
#     ${CMAKE_PROJECT_NAME} PRIVATE 
#     libcommon 
#     libcommunications 
#     libinference 
#     libxraydetection
# )