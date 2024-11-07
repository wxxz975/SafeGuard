# top 
cmake_minimum_required(VERSION 3.22)
project(SafeGuard)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

option(USE_TEST "compile test" ON)

find_package(nlohmann_json REQUIRED)


add_subdirectory(src)

if (USE_TEST) 
    add_subdirectory(test)
endif()
