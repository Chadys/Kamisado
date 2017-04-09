//
// Created by julie on 07/04/17.
//

#include "Case.h"

Case::Case(const TERMINAL_STYLES color_, const Pion &pion_)
    : color(color_), pion(pion_) {}

void Case::add_piece(TERMINAL_STYLES team, coord c) {
    this->pion = Pion(team,static_cast<TERMINAL_STYLES>(this->color-16), c);
}
