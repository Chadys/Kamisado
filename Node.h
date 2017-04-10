//
// Created by julie on 09/04/17.
//

#ifndef KAMISADO_NODE_H
#define KAMISADO_NODE_H


#include <vector>
#include "Movement.h"

class Node {
public:
    Node *parent;
    std::vector<Node *> children;
    unsigned int victories;
    unsigned int n_playouts;
    unsigned int depth;
    Movement from_move; //move done to obtain this node
    std::vector<Movement> moves_to; //moves that can be done from this node

    Node(Node *parent_ = nullptr, unsigned int depth_ = 0, Movement from_move_ = Movement());
    ~Node();
    double UTC_eval() const;
    static bool UCT_comp(const Node *n1, const Node *n2);
    static bool best_comp(const Node *n1, const Node *n2);
};


#endif //KAMISADO_NODE_H
