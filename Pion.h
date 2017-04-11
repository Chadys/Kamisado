//
// Created by julie on 07/04/17.
//

#ifndef KAMISADO_PION_H
#define KAMISADO_PION_H


#include <vector>
#include "header.h"

class Pion {
public:
    TERMINAL_STYLES team;
    TERMINAL_STYLES color;
    coord pos;
    static const Pion null;
    static const std::vector<TERMINAL_STYLES> possible_colors;

    Pion(TERMINAL_STYLES team_, TERMINAL_STYLES color_, coord pos_);
    bool operator==(const Pion &pion_) const;
    bool operator!=(const Pion &pion_) const;
};


#endif //KAMISADO_PION_H