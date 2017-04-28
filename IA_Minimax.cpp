////
// Created by julie on 20/04/17.
//

#include "IA_Minimax.h"

IA_Minimax::IA_Minimax() : first_move(true), team(GRAY), next_move_color(GRAY){}

void IA_Minimax::init(const char *file){
    this->b.init(file);
}


void IA_Minimax::move(Movement m) {
    if (this->first_move) {
        this->team = WHITE;
        this->first_move = false;
    }
    this->next_move_color =
            static_cast<TERMINAL_STYLES>(this->b.cases[m.fin.x][m.fin.y].color - 16);
    this->b.move(m);
    this->last_move = m.fin;
}

double IA_Minimax::max(TERMINAL_STYLES adv_team, int profondeur)
{
    TERMINAL_STYLES current_team = invert_color(adv_team);
    int check = check_end(this->last_move, adv_team);
    if(check != 0) {
        return check;
    }

    if(profondeur == 0)
    {
        return eval(this->last_move, adv_team);
    }

    double max = -1;
    auto possible_moves = this->get_moves(this->next_move_color, current_team);

    for(auto it = possible_moves.begin(); it < possible_moves.end(); ++it)
    {
        Movement move = *it;
        this->move(move);
        double score = this->min(current_team, profondeur - 1);
        if(score > max)
        {
            max = score;
        }
        this->move({move.fin, move.dep});
    }
    return max;
}

double IA_Minimax::min(TERMINAL_STYLES adv_team, int profondeur)
{
    TERMINAL_STYLES current_team = invert_color(adv_team);
    int check = check_end(this->last_move, adv_team);
    if(check != 0) {
        return check;
    }

    if(profondeur == 0)
    {
        return eval(this->last_move, adv_team);
    }

    double min = 1;
    auto possible_moves = this->get_moves(this->next_move_color, current_team);

    for(auto it = possible_moves.begin(); it < possible_moves.end(); ++it)
    {
        Movement move = *it;
        this->move(move);
        double score = this->max(current_team, profondeur - 1);
        if(score < min)
        {
            min = score;
        }
        this->move({move.fin, move.dep});
    }
    return min;
}

Movement IA_Minimax::genmove()
{
    int profondeur = 5;
    if (this->first_move)
    {
        this->team = BLACK;
        this->first_move = false;
        profondeur = 2;
    }


    TERMINAL_STYLES current_team = this->team;
    auto possible_moves = this->get_moves(this->next_move_color, current_team);
    Movement selected_move;
    double max = -1;
    for(auto it = possible_moves.begin(); it < possible_moves.end(); ++it)
    {
        Movement move = *it;
        this->move(move);
        double score = this->min(current_team, profondeur - 1);
        if(score > max)
        {
            max = score;
            selected_move = *it;
        }
        this->move({move.fin, move.dep});
    }

    return selected_move;
}

std::vector<Movement> IA_Minimax::get_moves(TERMINAL_STYLES color, TERMINAL_STYLES team, bool eval) const{
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

int IA_Minimax::check_end(coord &last_move, TERMINAL_STYLES last_play_team){
    if (last_move.x == static_cast<int>(this->b.finish[last_play_team])){
        if (last_play_team == this->team) //IA won
            return 1;
        return -1; //IA lost
    }
    return 0; //Game not finished
}

double IA_Minimax::eval(coord &last_move, TERMINAL_STYLES last_play_team){
    double test_end = this->check_end(last_move, last_play_team);
    std::vector<Movement> my_moves, enemy_moves;
    TERMINAL_STYLES enemy_team = invert_color(this->team);

    if (test_end)
        return test_end;
    my_moves = this->get_moves(GRAY, this->team, true);
    enemy_moves = this->get_moves(GRAY, enemy_team, true);

    for (Movement m :my_moves)
        if (m.fin.x == static_cast<int>(this->b.finish[this->team]))
            test_end++;
    for (Movement m : enemy_moves)
        if (m.fin.x == static_cast<int>(this->b.finish[enemy_team]))
            test_end--;
    return test_end/(this->b.pions.size()/2);
}