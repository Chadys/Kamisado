cmake_minimum_required(VERSION 3.5)
project(Kamisado)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h IA.cpp IA.h Movement.cpp Movement.h Node.cpp Node.h)
set(SOURCE_FILES_DISPLAY mainDisplay.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h Display.cpp Display.h)
add_executable(Kamisado ${SOURCE_FILES})
add_executable(DisplayKamisado ${SOURCE_FILES_DISPLAY})

find_package(SDL2 REQUIRED)
string(STRIP ${SDL2_INCLUDE_DIRS} SDL2_INCLUDE_DIRS)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(DisplayKamisado ${SDL2_LIBRARIES})