file(GLOB PROJECT_SOURCES UI/*)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Xray
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(Xray
        ${PROJECT_SOURCES}
    )
endif()


target_link_libraries(Xray PRIVATE "${ElaLib}")
target_link_libraries(Xray PRIVATE "${OnnLib}")
target_link_libraries(Xray PRIVATE "${LIBRARIES_LIST}")
target_link_libraries(Xray PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
