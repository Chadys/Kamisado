//
// Created by julie on 08/04/17.
//

#ifndef KAMISADO_MOVEMENT_H
#define KAMISADO_MOVEMENT_H


#include <ostream>
#include "header.h"

class Movement {
public:
    coord dep;
    coord fin;

    Movement(coord dep_ = {0,0}, coord fin_ = {0,0});
};
std::ostream &operator << (std::ostream &os, const Movement &m);


#endif //KAMISADO_MOVEMENT_H
