//
// Created by julie on 07/04/17.
//

#ifndef KAMISADO_CASE_H
#define KAMISADO_CASE_H

#include <memory>
#include "header.h"
#include "Pion.h"

class Case {
public:
    TERMINAL_STYLES color;
    Pion *pion;

    Case(const TERMINAL_STYLES color_ = BG_GRAY, Pion *pion_ = nullptr);
    ~Case();
};


#endif //KAMISADO_CASE_H
