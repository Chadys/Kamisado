//
// Created by julie on 07/04/17.
//

#include <sstream>
#include <iostream>
#include "Board.h"
#include "IA.h"

void command_input(IA ia);

int main() {
    IA ia;
    command_input(ia);
    return 0;
}

void command_input(IA ia){
    std::string line, command;
    while (std::getline(std::cin, line)){ //wait for user input
        std::istringstream sstream(line);
        sstream >> command;
        if (command == "quit")
            exit(EXIT_SUCCESS);
        if (command == "init"){
            ia.b.init("./default_board.kms");
            ia.b.print();
            continue;
        }
        if (command == "move"){
            coord dep, fin;
            sstream >> dep.x;
            sstream >> dep.y;
            sstream >> command;
            sstream >> fin.x;
            sstream >> fin.y;
            ia.move(dep, fin);
            ia.b.print();
            continue;
        }
    }
}