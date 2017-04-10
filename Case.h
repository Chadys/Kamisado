//
// Created by julie on 07/04/17.
//

#ifndef KAMISADO_CASE_H
#define KAMISADO_CASE_H

#include "header.h"
#include "Pion.h"

class Case {
public:
    TERMINAL_STYLES color;
    Pion pion;

    Case(const TERMINAL_STYLES color_ = BG_GRAY, const Pion &pion_ = Pion::null);
    void add_piece(TERMINAL_STYLES team, coord c);
};


#endif //KAMISADO_CASE_H
