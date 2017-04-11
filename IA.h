//
// Created by julie on 08/04/17.
//

#ifndef KAMISADO_IA_H
#define KAMISADO_IA_H


#include "Board.h"
#include "Movement.h"
#include "Node.h"

class IA {
public:
    Board b;
    static double UCT_const;

    IA();
    void move(Movement m);
    Movement genmove();

private:
    bool first_move;
    TERMINAL_STYLES team;
    TERMINAL_STYLES next_move_color = GRAY;
    Node *MC_tree;
    static unsigned int max_depth;
    static unsigned int max_playouts;
    std::map<TERMINAL_STYLES, unsigned int> finish;

    static Movement best_move(const std::vector<Node*> &successors);
    std::vector<Movement> get_moves(TERMINAL_STYLES color, TERMINAL_STYLES team) const;
    void playouts(Node *n);
    int check_end(Movement last_move);
};


#endif //KAMISADO_IA_H
