cmake_minimum_required(VERSION 3.10)

add_library(imgui STATIC
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
    back/rlImGui.cpp
)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/back
)

target_compile_features(imgui PUBLIC cxx_std_20)

target_compile_definitions(imgui PUBLIC IMGUI_IMPL_API= NO_FONT_AWESOME)

target_link_libraries(imgui PUBLIC raylib)
