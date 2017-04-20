cmake_minimum_required(VERSION 3.5)
project(Kamisado)

set(CMAKE_CXX_STANDARD 14)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -Wextra -Wall" )
set(SOURCE_FILES_MCTS main_ia_mcts.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h IA_MCTS.cpp IA_MCTS.h Movement.cpp Movement.h Node.cpp Node.h)
add_executable(Kamisado_IA_MCTS ${SOURCE_FILES_MCTS})

set(SOURCE_FILES_ARBITER main_arbiter.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h Movement.cpp Movement.h Arbiter.cpp Arbiter.h)
add_executable(Kamisado_Arbiter ${SOURCE_FILES_ARBITER})

set(SOURCE_FILES_MINIMAX main_ia_minimax.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h IA_Minimax.cpp IA_Minimax.h Movement.cpp Movement.h)
add_executable(Kamisado_IA_MINIMAX ${SOURCE_FILES_MINIMAX})