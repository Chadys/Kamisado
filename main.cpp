//
// Created by julie on 07/04/17.
//

#include <sstream>
#include <iostream>
#include "Board.h"

void command_input(Board &b);

int main() {
    Board b("../default_board.kms");
    b.print();
    command_input(b);
    return 0;
}

void command_input(Board &b){
    std::string line, command;
    while (std::getline(std::cin, line)){ //wait for user input
        std::istringstream sstream(line);
        sstream >> command;
        if (command == "quit")
            exit(EXIT_SUCCESS);
        if (command == "move"){
            coord dep, fin;
            sstream >> dep.x;
            sstream >> dep.y;
            sstream >> command;
            sstream >> fin.x;
            sstream >> fin.y;
            b.move(dep, fin);
            b.print();
        }
    }
}