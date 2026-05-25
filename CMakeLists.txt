cmake_minimum_required(VERSION 3.10)
project(Roguelike)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and configure ncurses.
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

# Source files.
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/enemy.cpp
    src/level.cpp
    src/fov.cpp
)

# Create executable.
add_executable(roguelike ${SOURCES})

target_include_directories(roguelike PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CURSES_INCLUDE_DIRS}
)

# Link ncurses.
target_link_libraries(roguelike PRIVATE ${CURSES_LIBRARIES})

# compiler warnings.
target_compile_options(roguelike PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)