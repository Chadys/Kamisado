//
// Created by julie on 08/04/17.
//

#include "IA.h"


double IA::UCT_const = 0.4;

IA::IA() : first_move(true), team(GRAY), next_move_color(GRAY), max_depth(100), max_playouts(5) {}

void IA::init(const char *file){
    this->b.init(file);
}


void IA::move(Movement m) {
    if (this->first_move) {
        this->team = WHITE;
        this->first_move = false;
        this->max_playouts = 50;
    }
    this->next_move_color =
            static_cast<TERMINAL_STYLES>(this->b.cases[m.fin.x][m.fin.y].color - 16);
    this->b.move(m);
}


Movement IA::genmove() {
    Movement selected_move;
    Node *ptr, *child;
    unsigned int depth;
    TERMINAL_STYLES current_team;

    if (this->first_move) {
        this->team = BLACK;
        this->first_move = false;
        this->max_playouts = 50;
    }
    this->MC_tree = new Node;
    this->MC_tree->moves_to = this->get_moves(this->next_move_color, this->team);
    while (true){
            /***selection***/
        //while chosen node is fully expanded, keep going down
        for (depth = 0, ptr = this->MC_tree;
             !ptr->moves_to.empty() && ptr->children.size() == ptr->moves_to.size();
             depth++) {
            ptr = *std::max_element(ptr->children.begin(), ptr->children.end(), Node::UCT_comp);
            this->move(ptr->from_move);
        }
        //if terminal node selected
        if (ptr->moves_to.empty() || depth >= this->max_depth){
            //go back to starting pos
            for(; ptr != MC_tree; ptr = ptr->parent)
                this->move({ptr->from_move.fin, ptr->from_move.dep});
            break;
        }

            /***expansion***/
        //create new child
        selected_move = ptr->moves_to[ptr->children.size()];
        child = new Node(ptr, depth+1, selected_move);
        ptr->children.push_back(child);
        this->move(selected_move);
        current_team = depth%2 ? invert_color(this->team) : this->team;
        if(!check_end(selected_move.fin, current_team))
            child->moves_to = this->get_moves(static_cast<TERMINAL_STYLES>(
                                                      this->b.cases[selected_move.fin.x][selected_move.fin.y].color-16),
                                              invert_color(current_team));

            /***simulation***/
        playouts(child);

            /***backpropagation***/
        for(ptr = child; ptr != MC_tree; ptr = ptr->parent){
            ptr->parent->victories += ptr->victories;
            ptr->parent->n_playouts += ptr->n_playouts;
            this->move({ptr->from_move.fin, ptr->from_move.dep});
        }
    }
    selected_move =  best_move(MC_tree->children);
    this->move(selected_move);
    delete this->MC_tree;
    return selected_move;
}

Movement IA::best_move(const std::vector<Node*> &successors){
    return (*std::max_element(successors.cbegin(), successors.cend(), Node::best_comp))->from_move;
}

std::vector<Movement> IA::get_moves(TERMINAL_STYLES color, TERMINAL_STYLES team, bool eval) const{
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
    // pass
    moves.push_back({pos, pos});
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
    // favor the biggest distances and the front
    std::reverse(moves.begin(),moves.end());
    return moves;
}

void IA::playouts(Node *n){
    double result;
    Case &c = this->b.cases[n->from_move.fin.x][n->from_move.fin.y];
    std::random_device rd;
    std::mt19937 gen(rd());
    TERMINAL_STYLES current_team = c.pion->team;
    unsigned int current_depth = n->depth;

    result = eval(n->from_move.fin, current_team);
    if (n->moves_to.empty() || current_depth == this->max_depth){
        n->victories += result;
        n->n_playouts++;
        return;
    }
    for (unsigned int i = 0; i < this->max_playouts; ++i, current_team = c.pion->team, current_depth = n->depth) {
        std::vector<Movement> next_moves(n->moves_to);
        std::vector<Movement> playout_moves;
        Movement m;

        while (!next_moves.empty() && current_depth < this->max_depth){
            current_team = invert_color(current_team);
            current_depth++;
            m = choose_playout_move(next_moves, gen, current_team);
            this->move(m);
            playout_moves.push_back({m.fin, m.dep});
            if(fabs(result = eval(m.fin, current_team)) != 1)
                next_moves = this->get_moves(static_cast<TERMINAL_STYLES>(this->b.cases[m.fin.x][m.fin.y].color-16),
                                             invert_color(current_team));
            else
                next_moves.clear();
        }
        std::for_each(playout_moves.crbegin(), playout_moves.crend(),
            [&, this, current_depth, current_team](Movement m) mutable { this->move(m); });
        n->victories += result;
        n->n_playouts++;
    }
}

int IA::check_end(coord &last_move, TERMINAL_STYLES last_play_team){
    if (last_move.x == static_cast<int>(this->b.finish[last_play_team])){
        if (last_play_team == this->team) //IA won
            return 1;
        return -1; //IA lost
    }
    return 0; //Game not finished
}

Movement IA::choose_playout_move(std::vector<Movement> &moves, std::mt19937 &gen, TERMINAL_STYLES current_team){
    for (Movement& m : moves){
        if(m.fin.x == static_cast<int>(this->b.finish[current_team]))
            return m;
    }
    std::uniform_int_distribution<unsigned int> dis(0,moves.size()-1);
    return moves[dis(gen)];
}

double IA::eval(coord &last_move, TERMINAL_STYLES last_play_team){
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