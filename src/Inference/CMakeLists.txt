# library Inference
project(Inference)
set(targetname libinference)

set(curdir ${PROJECT_SOURCE_DIR})


# 查找 OpenCV
find_package(OpenCV REQUIRED)


# 查找 OpenVINO
find_package(OpenVINO REQUIRED)

find_package(fmt REQUIRED)


# ONNX Runtime, mannul set path,
include_directories("/usr/include/onnxruntime")



file(GLOB_RECURSE CPP_FILES "src/*.cpp")
foreach(filepath ${CPP_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND sources_files ${filename})
endforeach(filepath ${SOURCE_FILE})


# file(GLOB_RECURSE INTER_HDR_FILES "src/*.h")
# # foreach(filepath ${CPP_FILES})
# #     string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
# #     list(APPEND inter_header_files ${filename})
# # endforeach(filepath ${SOURCE_FILE})


add_library(
    ${targetname} STATIC 
    ${sources_files}
)


target_include_directories(
    ${targetname} PRIVATE 
    ${OpenCV_INCLUDE_DIRS}
    ${OpenVINO_INCLUDE_DIRS}
    
)

target_include_directories(
    ${targetname} PUBLIC 
    ${curdir}/include
    ${curdir}/src
)


target_link_libraries(
    ${targetname} PRIVATE
    ${OpenCV_LIBS}
    openvino::runtime
    onnxruntime
    libcommon
    fmt::fmt
)


