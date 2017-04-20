//
// Created by julie on 11/04/17.
//

#ifndef KAMISADO_ARBITER_H
#define KAMISADO_ARBITER_H


#include "Board.h"

class Arbiter {
public:
    unsigned short game_ended;

    Arbiter();
    void init(const char *file);
    unsigned short move(Movement &m);
    void resign();

private:
    Board b;
    TERMINAL_STYLES next_team;
    TERMINAL_STYLES next_move_color;

    bool check_legal(Movement m) const;
    bool check_end(coord &last_move);
};


#endif //KAMISADO_ARBITER_H
