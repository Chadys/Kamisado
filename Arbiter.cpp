//
// Created by julie on 11/04/17.
//

#include "Arbiter.h"


Arbiter::Arbiter() : next_team(BLACK), next_move_color(GRAY), play_ended(false) {}

void Arbiter::init(const char *file){
    this->b.init(file);
}

unsigned short Arbiter::move(Movement &m) {
    if(play_ended || !this->check_legal(m))
        return 0;
    if(this->check_end(m.fin)) {
        this->play_ended = true;
        return 2;
    }
    this->next_move_color =
            static_cast<TERMINAL_STYLES>(this->b.cases[m.fin.x][m.fin.y].color - 16);
    this->next_team = invert_color(this->next_team);
    this->b.move(m);
    return 1;
}

bool Arbiter::check_legal(Movement m) const{
    int front = next_team == BLACK ? 1 : -1;
    int side = m.fin.y - m.dep.y;
    if(side)
        side /= abs(side);

    //check move in board's limits
    if(m.dep.x < 0 || m.dep.x >= static_cast<int>(this->b.cases.size()) ||
            m.dep.y < 0 || m.dep.y >= static_cast<int>(this->b.cases[0].size()) ||
            m.fin.x < 0 || m.fin.x >= static_cast<int>(this->b.cases.size()) ||
            m.fin.y < 0 || m.fin.y >= static_cast<int>(this->b.cases[0].size()))
        return false;

    //check piece of correct color moved
    if (this->next_move_color != GRAY && this->b.cases[m.dep.x][m.dep.y].pion->color != this->next_move_color)
        return false;

    //check piece of correct team moved
    if (this->b.cases[m.dep.x][m.dep.y].pion->team != this->next_team)
        return false;

    //check piece doesn't move back
    if (m.dep.x*front > m.fin.x*front)
        return false;

    //check piece didn't pass if it could move
    if (m.dep.x == m.fin.x && m.dep.y == m.fin.y){
        const std::vector<Case> &line = this->b.cases[m.dep.x+front];
        if(line[m.dep.y].pion == nullptr || //possibility to move front
           (m.dep.y > 0 && line[m.dep.y-1].pion == nullptr) || //diag left
           (m.dep.y < static_cast<int>(line.size())-1 && line[m.dep.y+1].pion == nullptr)) //diag right
            return false;
        return true;
    }

    //check no piece on the way and piece could move there
    while (m.dep.x != m.fin.x || m.dep.y != m.fin.y){
        m.dep.x += front;
        m.dep.y += side;
        if(m.dep.x < 0 || m.dep.x >= static_cast<int>(this->b.cases.size()) ||
           m.dep.y < 0 || m.dep.y >= static_cast<int>(this->b.cases[0].size()))
            return false;
        if (this->b.cases[m.dep.x][m.dep.y].pion != nullptr)
            return false;
    }

    return true;
}


bool Arbiter::check_end(coord &last_move){
    if (last_move.x == static_cast<int>(this->b.finish[this->next_team]))
            return true; //Player that just played won
    return false; //Game not finished
}