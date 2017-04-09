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

    IA();
    void move(Movement m);
    Movement genmove();

private:
    TERMINAL_STYLES team;
    bool first_move;
    TERMINAL_STYLES next_move_color = GRAY;
    Node *MC_tree;
    static unsigned int max_depth;

    int eval() const;
    Movement best_move(std::vector<Node*> successors);
};


#endif //KAMISADO_IA_H
