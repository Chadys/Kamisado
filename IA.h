//
// Created by julie on 08/04/17.
//

#ifndef KAMISADO_IA_H
#define KAMISADO_IA_H


#include "Board.h"

class IA {
public:
    IA() {}
    void init(Board &b, TERMINAL_STYLES team);

private:
    Board b;
    TERMINAL_STYLES team;
};


#endif //KAMISADO_IA_H
