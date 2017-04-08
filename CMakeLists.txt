cmake_minimum_required(VERSION 3.6)
project(Kamisado)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h IA.cpp IA.h)
add_executable(Kamisado ${SOURCE_FILES})