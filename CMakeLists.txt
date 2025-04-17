cmake_minimum_required(VERSION 3.5)

project(Xray VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    m_mainpage.h m_mainpage.cpp
    m_settings.h m_settings.cpp
    m_homepage.h m_homepage.cpp
    m_screen.h m_screen.cpp
    m_modelsettings.h m_modelsettings.cpp
    m_selectionsettings.h m_selectionsettings.cpp
    m_count.h m_count.cpp
    #
    m_videocore.h m_videocore.cpp
    m_videoif.h m_videoif.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Xray
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Xray APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Xray SHARED
            ${PROJECT_SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
else()
    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/linux")
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/linux/Ela")
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/linux/onnruntime")
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/linux/opencv")
    elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
        link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/win")
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/win/Ela")
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/win/onnruntime")
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/win/opencv")
    endif()
    add_executable(Xray
        ${PROJECT_SOURCES}
    )
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(Xray PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/Ela/libElaWidgetTools.so")
    target_link_libraries(Xray PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/onnruntime/libonnxruntime.so.1.18.0")
    file(GLOB LIBRARIES_LIST "${CMAKE_SOURCE_DIR}/lib/linux/opencv/libopencv*")
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(Xray PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/win/Ela/ElaWidgetTools.lib")
    target_link_libraries(Xray PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/win/onnruntime/onnxruntime.lib")
    file(GLOB LIBRARIES_LIST "${CMAKE_SOURCE_DIR}/lib/win/opencv/*.lib")
endif()
target_link_libraries(Xray PRIVATE "${LIBRARIES_LIST}")
endif()
endif()

target_link_libraries(Xray PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

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
