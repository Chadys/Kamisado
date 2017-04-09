//
// Created by julie on 09/04/17.
//

#include "Node.h"


Node::~Node(){
    for (auto child : this->children)
    delete child;
}