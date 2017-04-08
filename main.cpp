//
// Created by julie on 07/04/17.
//

#include <sstream>
#include <iostream>
#include "Board.h"
#include "IA.h"

void command_input(Board &b, IA ia);

int main() {
    Board b;
    IA ia;
    b.print();
    command_input(b, ia);
    return 0;
}

void command_input(Board &b, IA ia){
    std::string line, command;
    while (std::getline(std::cin, line)){ //wait for user input
        std::istringstream sstream(line);
        sstream >> command;
        if (command == "quit")
            exit(EXIT_SUCCESS);
        if (command == "init"){
            int t;
            sstream >> t;
            b.init("./default_board.kms");
            ia.init(b, t ? WHITE : BLACK);
        }
        if (command == "move"){
            coord dep, fin;
            sstream >> dep.x;
            sstream >> dep.y;
            sstream >> command;
            sstream >> fin.x;
            sstream >> fin.y;
            b.move(dep, fin);
            b.print();
            continue;
        }
    }
}