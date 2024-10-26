


add_subdirectory(Common)
add_subdirectory(Inference)
add_subdirectory(Networks)
#add_subdirectory(SafeGuard)


add_executable(
    ${CMAKE_PROJECT_NAME}
    main.cpp
)


target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    # libcommon
    # libinference
    # libnetworks
    # libsafeguard
)


