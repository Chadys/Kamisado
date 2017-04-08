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
    Board(const char *file);
    void print() const;
    void move(coord dep, coord fin);

private:
    std::vector<std::vector<Case>> cases;
    static std::map<char, TERMINAL_STYLES> color_map;

    void add_pieces();
};


#endif //KAMISADO_BOARD_H
