//
// Created by julie on 08/04/17.
//

#include "IA.h"


IA::IA() : first_move(true), team(GRAY) {}


void IA::move(Movement m){
    Case &old_c = this->b.cases[m.dep.x][m.dep.y];
    Case &new_c = this->b.cases[m.fin.x][m.fin.y];
    new_c.pion = old_c.pion;
    old_c.pion = Pion::null;
    if (this->first_move) {
        this->team = WHITE;
        this->first_move = false;
    }
    this->next_move_color = static_cast<TERMINAL_STYLES>(new_c.color-16);
}

int IA::eval(){

};

Movement IA::genmove() {

}