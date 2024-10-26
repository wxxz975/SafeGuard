# library Common
project(Common)
set(targetname libcommon)

set(curdir ${PROJECT_SOURCE_DIR})


file(GLOB_RECURSE CPP_FILES "src/*.cpp")
foreach(filepath ${CPP_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND sources_files ${filename})
endforeach(filepath ${SOURCE_FILE})


add_library(
    ${targetname} STATIC 
    ${sources_files}
)

target_include_directories(
    ${targetname} PUBLIC 
    ${curdir}/include
)



