cmake_minimum_required(VERSION 3.16)
project(GameOfLife CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_executable(game_of_life ${SRC_FILES})

target_include_directories(game_of_life PRIVATE include)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/lib/cmake/SFML")
find_package(SFML COMPONENTS Graphics Window System REQUIRED)

target_link_libraries(game_of_life PRIVATE SFML::Graphics SFML::Window SFML::System)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy SFML DLLs
set(SFML_DLLS
    "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-graphics-d-3.dll"
    "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-window-d-3.dll"
    "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-system-d-3.dll"
    "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-graphics-3.dll"
    "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-window-3.dll"
    "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/bin/sfml-system-3.dll"
)

foreach(DLL ${SFML_DLLS})
    add_custom_command(TARGET game_of_life POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL}
        $<TARGET_FILE_DIR:game_of_life>
    )
endforeach()