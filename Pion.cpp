//
// Created by julie on 07/04/17.
//

#include "Pion.h"

Pion::Pion(TERMINAL_STYLES team_, TERMINAL_STYLES color_)
    : team(team_), color(color_) {}

const Pion Pion::null(GRAY, RESET);

bool Pion::operator==(const Pion &pion_) const{
    return this->color == pion_.color && this->team == pion_.team;
}

bool Pion::operator!=(const Pion &pion_) const{
    return !(*this == pion_);
}

Pion::operator bool() const{
    return *this != Pion::null;
}