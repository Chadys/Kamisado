//
// Created by julie on 07/04/17.
//

#include "Pion.h"

Pion::Pion(TERMINAL_STYLES team_, TERMINAL_STYLES color_, coord pos_)
    : team(team_), color(color_), pos(pos_) {}

const Pion Pion::null(GRAY, RESET, {-1, -1});

const std::vector<TERMINAL_STYLES> Pion::possible_colors = {CYAN, BLUE, PURPLE, BRIGHTRED, YELLOW, RED, GREEN, BROWN};

bool Pion::operator==(const Pion &pion_) const{
    return this->color == pion_.color && this->team == pion_.team;
}

bool Pion::operator!=(const Pion &pion_) const{
    return !(*this == pion_);
}