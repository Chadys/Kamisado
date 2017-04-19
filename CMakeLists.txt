cmake_minimum_required(VERSION 3.5)
project(Kamisado)

set(CMAKE_CXX_STANDARD 14)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -Wextra -Wall" )

set(SOURCE_FILES_MINMAX main_ia.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h IA_minmax.cpp IA_minmax.h Movement.cpp Movement.h)
add_executable(Kamisado_IA_MINMAX ${SOURCE_FILES_MINMAX})