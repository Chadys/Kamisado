//
// Created by julie on 09/04/17.
//

#ifndef KAMISADO_NODE_H
#define KAMISADO_NODE_H


#include <vector>
#include "Movement.h"

class Node {
public:
    unsigned int victories;
    Node *parent;
    std::vector<Node *> children;
    std::vector<Movement> doable_moves;

    ~Node();
};


#endif //KAMISADO_NODE_H
