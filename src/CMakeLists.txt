


add_subdirectory(Common)
add_subdirectory(Inference)
#add_subdirectory(Networks)
#add_subdirectory(SafeGuard)


add_executable(
    ${CMAKE_PROJECT_NAME}
    main.cpp
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)


target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    # libcommon
    libinference
    # libnetworks
    # libsafeguard
)


