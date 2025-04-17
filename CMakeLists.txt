cmake_minimum_required(VERSION 3.5)

project(Xray VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/linux")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/linux/Ela")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/linux/onnruntime")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/linux/opencv")
    set(ElaLib "${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/Ela/libElaWidgetTools.so")
    set(OnnLib "${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/onnruntime/libonnxruntime.so.1.18.0")
    file(GLOB LIBRARIES_LIST "${CMAKE_SOURCE_DIR}/lib/linux/opencv/libopencv*")
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/win")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/win/Ela")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/win/onnruntime")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/win/opencv")
    set(ElaLib "${CMAKE_CURRENT_SOURCE_DIR}/lib/win/Ela/ElaWidgetTools.lib")
    set(OnnLib "${CMAKE_CURRENT_SOURCE_DIR}/lib/win/onnruntime/onnxruntime.lib")
    file(GLOB LIBRARIES_LIST "${CMAKE_SOURCE_DIR}/lib/win/opencv/*.lib")
endif()

add_subdirectory(src)

set_target_properties(Xray PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Xray
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Xray)
endif()
