file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "*.cpp"
    "logic/*.cpp"
    "render/*.cpp"
    "shared/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(${CMAKE_SOURCE_DIR}/external/imgui ${CMAKE_BINARY_DIR}/external/imgui-build)

target_compile_definitions(${PROJECT_NAME} PRIVATE NO_FONT_AWESOME)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib imgui)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
    COMMENT "Copying res to executable"
)