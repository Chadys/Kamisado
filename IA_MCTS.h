//
// Created by julie on 08/04/17.
//

#ifndef KAMISADO_IA_MCTS_H
#define KAMISADO_IA_MCTS_H


#include <random>
#include <algorithm>
#include <climits>
#include "Board.h"
#include "Movement.h"
#include "Node.h"

class IA_MCTS {
public:
    static double UCT_const;

    IA_MCTS();
    void init(const char *file);
    void move(Movement m);
    Movement genmove();

private:
    Board b;
    bool first_move;
    TERMINAL_STYLES team;
    TERMINAL_STYLES next_move_color;
    Node *MC_tree;
    unsigned int max_depth;
    unsigned int max_playouts;

    static Movement best_move(const std::vector<Node*> &successors);
    std::vector<Movement> get_moves(TERMINAL_STYLES color, TERMINAL_STYLES team, bool eval = false) const;
    void playouts(Node *n);
    int check_end(coord &last_move, TERMINAL_STYLES last_play_team);
    double eval(coord &last_move, TERMINAL_STYLES last_play_team);
    Movement choose_playout_move(std::vector<Movement> &moves, std::mt19937 &gen, TERMINAL_STYLES current_team);
};


#endif //KAMISADO_IA_MCTS_H
