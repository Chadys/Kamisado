//
// Created by julie on 07/04/17.
//

#ifndef KAMISADO_BOARD_H
#define KAMISADO_BOARD_H


#include <vector>
#include <map>
#include "Case.h"

class Board {
public:
    std::vector<std::vector<Case>> cases;
    std::vector<Pion&> pions;

    Board(){}
    void init(const char *file);
    void print() const;

private:
    static const std::map<char, TERMINAL_STYLES> color_map;

    void add_pieces();
};


#endif //KAMISADO_BOARD_H
