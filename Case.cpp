//
// Created by julie on 07/04/17.
//

#include "Case.h"

Case::Case(const TERMINAL_STYLES color_, Pion *pion_)
    : color(color_), pion(pion_) {}

Case::~Case() {
    delete this->pion;
}