//
// Created by julie on 08/04/17.
//

#include <climits>
#include <algorithm>
#include "IA.h"


unsigned int max_depth = UINT_MAX;

IA::IA() : first_move(true), team(GRAY) {}


void IA::move(Movement m){
    Case &old_c = this->b.cases[m.dep.x][m.dep.y];
    Case &new_c = this->b.cases[m.fin.x][m.fin.y];
    new_c.pion = old_c.pion;
    new_c.pion.pos = m.fin;
    old_c.pion = Pion::null;
    if (this->first_move) {
        this->team = WHITE;
        this->first_move = false;
    }
    this->next_move_color = static_cast<TERMINAL_STYLES>(new_c.color-16);
}

int IA::eval() const{

};

Movement IA::genmove() {
    bool stop = false;
    Movement chosen;

    if (this->first_move) {
        this->team = BLACK;
        this->first_move = false;
    }
    this->MC_tree = new Node;
    this->MC_tree->moves_to = this->get_moves(this->next_move_color, this->team);
    while (!stop){

    }
    chosen =  best_move(MC_tree->children);
    delete this->MC_tree;
    return chosen;
}

Movement IA::best_move(const std::vector<Node*> &successors){
    return (*std::max_element(successors.cbegin(), successors.cend()))->from_move;
}

std::vector<Movement> IA::get_moves(TERMINAL_STYLES color, TERMINAL_STYLES team) const{
    std::vector<Movement> moves;
    coord pos;
    int front = team == BLACK ? 1 : -1;
    if (color == GRAY){
        std::vector<Movement> tmp_moves;
        for (TERMINAL_STYLES col : Pion::possible_colors){
            tmp_moves = get_moves(col, team);
            moves.insert(moves.end(), std::make_move_iterator(tmp_moves.begin()), std::make_move_iterator(tmp_moves.end()));
        }
        return moves;
    }
    auto p = std::find(team == BLACK ? this->b.pions.cbegin() : this->b.pions.cbegin()+8,
                       this->b.pions.cend(), Pion(team, color, coord()));
    pos = (*p).pos;
    moves.push_back({pos, pos});
    // front line
    for(coord new_pos = {pos.x+front, pos.y};
        new_pos.x >= 0 && new_pos.x < this->b.cases.size() &&
                !this->b.cases[new_pos.x][new_pos.y].pion;
        new_pos = {new_pos.x+front, new_pos.y})
    {
        moves.push_back({pos, new_pos});
    }
    // left diag
    for(coord new_pos = {pos.x+front, pos.y-1};
        new_pos.x >= 0 && new_pos.x < this->b.cases.size() && new_pos.y >= 0 &&
                !this->b.cases[new_pos.x][new_pos.y].pion;
        new_pos = {new_pos.x+front, new_pos.y-1})
    {
        moves.push_back({pos, new_pos});
    }
    // right_diag
    for(coord new_pos = {pos.x+front, pos.y+1};
        new_pos.x >= 0 && new_pos.x < this->b.cases.size() && new_pos.y < this->b.cases[0].size() &&
                !this->b.cases[new_pos.x][new_pos.y].pion;
        new_pos = {new_pos.x+front, new_pos.y+1})
    {
        moves.push_back({pos, new_pos});
    }
    return moves;
}