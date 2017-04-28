cmake_minimum_required(VERSION 3.5)
project(Kamisado)

set(CMAKE_CXX_STANDARD 14)


SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -Wextra -Wall" )

set(SOURCE_FILES_MCTS main_ia_mcts.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h IA_MCTS.cpp IA_MCTS.h Movement.cpp Movement.h Node.cpp Node.h)
add_executable(Kamisado_IA_MCTS ${SOURCE_FILES_MCTS})

set(SOURCE_FILES_MINIMAX main_ia_minimax.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h IA_Minimax.cpp IA_Minimax.h Movement.cpp Movement.h)
add_executable(Kamisado_IA_Minimax ${SOURCE_FILES_MINIMAX})

set(SOURCE_FILES_RAMDOM main_ia_ramdom.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h IA_Ramdom.cpp IA_Ramdom.h Movement.cpp Movement.h)
add_executable(Kamisado_IA_Ramdom ${SOURCE_FILES_RAMDOM})

set(SOURCE_FILES_REFEREE main_referee.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h Movement.cpp Movement.h Referee.cpp Referee.h)
add_executable(Kamisado_Referee ${SOURCE_FILES_REFEREE})

set(SOURCE_FILES_DISPLAY main_Display.cpp header.h Board.cpp Board.h Case.cpp Case.h Pion.cpp Pion.h Display.cpp Display.h Movement.cpp Movement.h)
add_executable(Kamisado_Display ${SOURCE_FILES_DISPLAY})

#External libraries
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(Kamisado_Display ${SFML_LIBRARIES})

