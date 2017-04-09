//
// Created by julie on 07/04/17.
//

#include <fstream>
#include <iostream>
#include "Board.h"

void Board::init(const char *file) {
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


const std::map<char, TERMINAL_STYLES> Board::color_map =
        {{'O', BG_CYAN}, {'B', BG_BLUE}, {'V', BG_PURPLE}, {'P', BG_BRIGHTRED},
         {'Y', BG_YELLOW}, {'R', BG_RED}, {'G', BG_GREEN}, {'M', BG_BROWN}};


void Board::add_pieces() {
    unsigned int count, x;
    count = 0;
    for (Case &c : this->cases[0]) {
        c.add_piece(BLACK, {0, count});
        this->pions.push_back(&c.pion);
        count++;
    }
    count = 0;
    x = this->cases.size()-1;
    for (Case &c : this->cases[x]) {
        c.add_piece(WHITE, {x, count});
        this->pions.push_back(&c.pion);
        count++;
    }
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