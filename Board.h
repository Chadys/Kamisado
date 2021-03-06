//
// Created by julie on 07/04/17.
//

#ifndef KAMISADO_BOARD_H
#define KAMISADO_BOARD_H


#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "Case.h"
#include "Movement.h"

class Board {
public:
    std::vector<std::vector<Case>> cases;
    std::vector<Pion*> pions;
    std::map<TERMINAL_STYLES, unsigned int> finish;

    void init(const char *file);
    void print() const;
    void move(Movement m);

private:
    static const std::map<char, TERMINAL_STYLES> color_map;

    void add_pieces();
};


#endif //KAMISADO_BOARD_H
