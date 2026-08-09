file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "*.cpp"
    "logic/*.cpp"
    "render/*.cpp"
    "shared/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
    COMMENT "Copying res to executable"
)