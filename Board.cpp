//
// Created by julie on 07/04/17.
//

#include <fstream>
#include <iostream>
#include "Board.h"

Board::Board(const char *file) {
    std::ifstream stream(file);
    char c;

    this->cases = std::vector<std::vector<Case>>();
    std::vector<Case> line = std::vector<Case>();
    while(stream >> std::noskipws >> c){
        if(c == '\n'){
            this->cases.push_back(line);
            line = std::vector<Case>();
            continue;
        }
        line.push_back(Case(color_map.at(c)));
    }
    this->cases.push_back(line);
    stream.close();
    this->add_pieces();
}


std::map<char, TERMINAL_STYLES> Board::color_map =
        {{'O', BG_CYAN}, {'B', BG_BLUE}, {'V', BG_PURPLE}, {'P', BG_BRIGHTRED},
         {'Y', BG_YELLOW}, {'R', BG_RED}, {'G', BG_GREEN}, {'M', BG_BROWN}};


void Board::add_pieces() {
    for (Case &c : this->cases[0])
        c.add_piece(BLACK);
    for (Case &c : this->cases[this->cases.size()-1])
        c.add_piece(WHITE);
}


void Board::print() const{
    for(auto &row : this->cases){
        for (const Case &c : row) {
            std::cout << codeFromStyle(BOLD) << codeFromStyle(c.color);
            if (c.pion)
                std::cout << codeFromStyle(c.pion.team) << '['
                          << codeFromStyle(c.pion.color) << codeFromStyle(c.color) << codeFromStyle(BOLD) << 'o'
                          << codeFromStyle(c.pion.team) << codeFromStyle(c.color) << codeFromStyle(BOLD) << ']';
            else
                std::cout << "   ";
        }
        std::cout << codeFromStyle(RESET) << std::endl;
    }
    std::cout << codeFromStyle(RESET) << std::endl;
}


void Board::move(coord dep, coord fin){
    Case &old_c = this->cases[dep.x][dep.y];
    Case &new_c = this->cases[fin.x][fin.y];
    new_c.pion = old_c.pion;
    old_c.pion = Pion::null;
}