cmake_minimum_required(VERSION 3.10)
project(Roguelike)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Find and configure ncurses
find_package(Curses REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/enemy.cpp
    src/level.cpp
    src/room.cpp
)

# Header files
set(HEADERS
    include/game.h
    include/player.h
    include/enemy.h
    include/level.h
    include/vector2d.h
    include/room.h
)

# Create executable
add_executable(roguelike ${SOURCES} ${HEADERS})

# Link ncurses and include directories for project headers and ncurses
target_include_directories(roguelike PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(roguelike PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(roguelike PRIVATE ${CURSES_LIBRARIES})
