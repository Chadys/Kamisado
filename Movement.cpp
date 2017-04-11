//
// Created by julie on 08/04/17.
//

#include "Movement.h"


Movement::Movement(coord dep_, coord fin_) : dep(dep_), fin(fin_) {}

std::ostream &operator << (std::ostream &os, const Movement &m){
    os << m.dep.x << ' ' << m.dep.y << ' ' << m.fin.x << ' ' << m.fin.y;
    return os;
}