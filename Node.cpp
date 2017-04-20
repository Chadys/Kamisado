//
// Created by julie on 09/04/17.
//

#include "Node.h"
#include "IA_MCTS.h"


Node::Node(Node *parent_, unsigned int depth_, Movement from_move_)
        : parent(parent_), children(std::vector<Node *>()),
          victories(0), n_playouts(0), depth(depth_),
          from_move(from_move_), moves_to(std::vector<Movement>()) {}

Node::~Node(){
    for (auto child : this->children)
        delete child;
};

bool Node::UCT_comp(const Node *n1, const Node *n2){
    return n1->UTC_eval() < n2->UTC_eval();
}

bool Node::best_comp(const Node *n1, const Node *n2){
    return n1->victories/n1->n_playouts < n2->victories/n2->n_playouts;
}

double Node::UTC_eval() const{
    return (this->victories/this->n_playouts) +
            IA_MCTS::UCT_const*sqrt(log(this->parent->n_playouts)/this->n_playouts);
}