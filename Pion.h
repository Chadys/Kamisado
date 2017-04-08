//
// Created by julie on 07/04/17.
//

#ifndef KAMISADO_PION_H
#define KAMISADO_PION_H


#include "header.h"

class Pion {
public:
    TERMINAL_STYLES color;
    TERMINAL_STYLES team;
    static const Pion null;

    Pion(TERMINAL_STYLES team_, TERMINAL_STYLES color_);
    bool operator==(const Pion &pion_) const;
    bool operator!=(const Pion &pion_) const;
    explicit operator bool() const;
};


#endif //KAMISADO_PION_H