//
// ReCreated by Alexis on 19/04/17.
//

#include "IA_Ramdom.h"

IA_Ramdom::IA_Ramdom() : first_move(true), team(GRAY), next_move_color(GRAY) {}

void IA_Ramdom::init(const char *file){
    this->b.init(file);
}


void IA_Ramdom::move(Movement m) {
    if (this->first_move) {
        this->team = WHITE;
        this->first_move = false;
    }
    this->next_move_color =
            static_cast<TERMINAL_STYLES>(this->b.cases[m.fin.x][m.fin.y].color - 16);
    this->b.move(m);
}


Movement IA_Ramdom::genmove() {
    Movement selected_move;
    std::vector<Movement> moves;
    
    /* initialize random seed: */
    srand (time(NULL));

    if (this->first_move) {
        this->team = BLACK;
        this->first_move = false;
    }
    moves = get_moves(this->next_move_color, this->team);
    selected_move = moves[rand() % moves.size()];
    
    this->move(selected_move);
    return selected_move;
}


std::vector<Movement> IA_Ramdom::get_moves(TERMINAL_STYLES color, TERMINAL_STYLES team, bool eval) const{
    std::vector<Movement> moves;
    coord pos;
    int front = team == BLACK ? 1 : -1;

    if (color == GRAY){
        std::vector<Movement> tmp_moves;
        //eval needs to see all possible moves, but first move only need to see half as board is symetrical
        for (unsigned int i = 0 ; i < (eval ? Pion::possible_colors.size() : Pion::possible_colors.size()/2) ; i++){
            tmp_moves = get_moves(Pion::possible_colors[i], team);
            moves.insert(moves.end(), std::make_move_iterator(tmp_moves.begin()), std::make_move_iterator(tmp_moves.end()));
        }
        return moves;
    }

    auto p = ptr_find(team == BLACK ? this->b.pions.cbegin() : this->b.pions.cbegin()+this->b.pions.size()/2,
                       this->b.pions.cend(), Pion(team, color, coord()));
    pos = (*p)->pos;
    // left diag
    for(coord new_pos = {pos.x+front, pos.y-1};
        new_pos.x >= 0 && new_pos.x < static_cast<int>(this->b.cases.size()) && new_pos.y >= 0 &&
                this->b.cases[new_pos.x][new_pos.y].pion == nullptr;
        new_pos = {new_pos.x+front, new_pos.y-1})
    {
        moves.push_back({pos, new_pos});
    }
    // right_diag
    for(coord new_pos = {pos.x+front, pos.y+1};
        new_pos.x >= 0 && new_pos.x < static_cast<int>(this->b.cases.size()) && new_pos.y < static_cast<int>(this->b.cases[0].size()) &&
                this->b.cases[new_pos.x][new_pos.y].pion == nullptr;
        new_pos = {new_pos.x+front, new_pos.y+1})
    {
        moves.push_back({pos, new_pos});
    }
    // front line
    for(coord new_pos = {pos.x+front, pos.y};
        new_pos.x >= 0 && new_pos.x < static_cast<int>(this->b.cases.size()) &&
                this->b.cases[new_pos.x][new_pos.y].pion == nullptr;
        new_pos = {new_pos.x+front, new_pos.y})
    {
        moves.push_back({pos, new_pos});
    }
    // pass only if no other possibility
    if(moves.empty())
        moves.push_back({pos, pos});
    // favor the biggest distances and the front
    std::reverse(moves.begin(),moves.end());
    return moves;
}
