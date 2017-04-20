//
// Created by julie on 08/04/17.
//

#ifndef KAMISADO_IA_H
#define KAMISADO_IA_H


#include <random>
#include <algorithm>
#include <climits>
#include "Board.h"
#include "Movement.h"
#include "Node.h"

class IA {
public:
    static double UCT_const;

    IA();
    void init(const char *file);
    void move(Movement m);
    Movement genmove();
    double min(TERMINAL_STYLES current_team, int profondeur);
    double max(TERMINAL_STYLES current_team, int profondeur);

private:
    Board b;
    bool first_move;
    TERMINAL_STYLES team;
    TERMINAL_STYLES next_move_color;
    coord last_move;

    std::vector<Movement> get_moves(TERMINAL_STYLES color, TERMINAL_STYLES team, bool eval = false) const;
    int check_end(coord &last_move, TERMINAL_STYLES last_play_team);
    double eval(coord &last_move, TERMINAL_STYLES last_play_team);
};


#endif //KAMISADO_IA_H
