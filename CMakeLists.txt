cmake_minimum_required(VERSION 3.5)
project(Kamisado)

set(CMAKE_CXX_STANDARD 14)


SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -Wextra -Wall" )
set(SOURCE_FILES main_ia.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h IA.cpp IA.h Movement.cpp Movement.h Node.cpp Node.h)
set(SOURCE_FILES_DISPLAY mainDisplay.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h Display.cpp Display.h OtherDisplay.cpp OtherDisplay.h)
add_executable(Kamisado ${SOURCE_FILES})
add_executable(DisplayKamisado ${SOURCE_FILES_DISPLAY})

find_package(SDL2 REQUIRED)
string(STRIP ${SDL2_INCLUDE_DIRS} SDL2_INCLUDE_DIRS)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#find_package(SFML2 REQUIRED)
#include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(DisplayKamisado ${SDL2_LIBRARIES} ${Boost_LIBRARIES} )
#${SFML_LIBRARIES}