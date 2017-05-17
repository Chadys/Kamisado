//
// Created by julie on 11/04/17.
//

#include "Referee.h"
#include <unordered_set>


Referee::Referee() : game_ended(0), next_team(BLACK), next_move_color(GRAY) {}

void Referee::init(const char *file){
    this->b.init(file);
}

unsigned short Referee::move(Movement &m) {
    if(this->game_ended || !this->check_legal(m))
        return 0;
    if(this->check_end(m.fin)) {
        this->game_ended = static_cast<unsigned short>(this->next_team == BLACK ? 1 : 2);
        return 2;
    }
    this->next_move_color =
            static_cast<TERMINAL_STYLES>(this->b.cases[m.fin.x][m.fin.y].color - 16);
    this->next_team = invert_color(this->next_team);
    this->b.move(m);
    if(this->check_deadlock()) {
        this->game_ended = static_cast<unsigned short>(this->next_team == BLACK ? 1 : 2);
        return 3;
    }
    return 1;
}

bool Referee::check_legal(Movement m) const{
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

    //check that there is a piece on starting pos
    if(this->b.cases[m.dep.x][m.dep.y].pion == nullptr)
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

bool Referee::check_end(coord &last_move){
    if (last_move.x == static_cast<int>(this->b.finish[this->next_team]))
            return true; //Player that just played won
    return false; //Game not finished
}

void Referee::resign(){
    this->game_ended = static_cast<unsigned short>(this->next_team == BLACK ? 2 : 1);
}

bool Referee::check_deadlock(){
    std::unordered_set<Pion*> deja_vu;
    TERMINAL_STYLES color = this->next_move_color;
    TERMINAL_STYLES team = this->next_team;
    Pion* p = *ptr_find(team == BLACK ? this->b.pions.cbegin() : this->b.pions.cbegin()+this->b.pions.size()/2,
                        this->b.pions.cend(), Pion(team, color, coord()));
    do{
        int front = team == BLACK ? 1 : -1;
        coord pos = p->pos;
        // left diag
        coord new_pos = {pos.x+front, pos.y-1};
        if (new_pos.x >= 0 && new_pos.x < static_cast<int>(this->b.cases.size()) && new_pos.y >= 0 &&
            this->b.cases[new_pos.x][new_pos.y].pion == nullptr)
            return false;
        // right_diag
        new_pos = {pos.x+front, pos.y+1};
        if (new_pos.x >= 0 && new_pos.x < static_cast<int>(this->b.cases.size()) && new_pos.y < static_cast<int>(this->b.cases[0].size()) &&
            this->b.cases[new_pos.x][new_pos.y].pion == nullptr)
            return false;
        // front line
        new_pos = {pos.x+front, pos.y};
        if (new_pos.x >= 0 && new_pos.x < static_cast<int>(this->b.cases.size()) &&
            this->b.cases[new_pos.x][new_pos.y].pion == nullptr)
            return false;
        deja_vu.insert(p);
        color = static_cast<TERMINAL_STYLES>(this->b.cases[pos.x][pos.y].color - 16);
        team = invert_color(team);
        p = *ptr_find(team == BLACK ? this->b.pions.cbegin() : this->b.pions.cbegin()+this->b.pions.size()/2,
                      this->b.pions.cend(), Pion(team, color, coord()));
    } while (deja_vu.find(p) == deja_vu.end());
    return true;
}
