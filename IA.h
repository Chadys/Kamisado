//
// Created by julie on 08/04/17.
//

#ifndef KAMISADO_IA_H
#define KAMISADO_IA_H


#include "Board.h"

class IA {
public:
    Board b;

    IA();
    void move(coord dep, coord fin);

private:
    TERMINAL_STYLES team;
    bool first_move;
    TERMINAL_STYLES next_move_color = GRAY;

    void eval();
};


#endif //KAMISADO_IA_H
