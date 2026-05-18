cmake_minimum_required(VERSION 3.10)
project(Roguelike)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/enemy.cpp
    src/level.cpp
    src/terminal_graphics.cpp
)

# Header files
set(HEADERS
    include/game.h
    include/player.h
    include/enemy.h
    include/level.h
    include/terminal_graphics.h
    include/vector2d.h
)

# Create executable
add_executable(roguelike ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(roguelike PRIVATE ${CMAKE_SOURCE_DIR}/include)
