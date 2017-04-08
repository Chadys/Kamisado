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
};
std::ostream &operator << (std::ostream &os, const Movement &m);


#endif //KAMISADO_MOVEMENT_H
