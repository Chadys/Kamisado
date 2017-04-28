//
// Created by julie on 11/04/17.
//

#ifndef KAMISADO_REFEREE_H
#define KAMISADO_REFEREE_H


#include "Board.h"

class Referee {
public:
    unsigned short game_ended;

    Referee();
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


#endif //KAMISADO_REFEREE_H
