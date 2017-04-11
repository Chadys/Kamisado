//
// Created by julie on 08/04/17.
//

#include "IA.h"


unsigned int IA::max_depth = 50;
unsigned int IA::max_playouts = 50;
double IA::UCT_const = 0.4;

IA::IA() : first_move(true), team(GRAY) {}

void IA::init(const char *file){
    this->b.init(file);
    this->finish = {{BLACK, this->b.cases.size()-1}, {WHITE, 0}};
}


void IA::move(Movement m) {
    if (this->first_move) {
        this->team = WHITE;
        this->first_move = false;
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
    auto p = ptr_find(team == BLACK ? this->b.pions.cbegin() : this->b.pions.cbegin()+8,
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
    int result;
    Case &c = this->b.cases[n->from_move.fin.x][n->from_move.fin.y];
    std::random_device rd;
    std::mt19937 gen(rd());

    result = check_end(n->from_move.fin, c.pion->team);
    if (n->moves_to.empty() || n->depth == this->max_depth){
        n->victories += result;
        n->n_playouts++;
        return;
    }
    for (unsigned int i = 0; i < max_playouts; ++i) {
        TERMINAL_STYLES current_team = invert_color(c.pion->team);
        std::vector<Movement> next_moves = n->moves_to;
        unsigned int current_depth = n->depth;
        Movement m;
        std::vector<Movement> playout_moves;

        while (!next_moves.empty() && current_depth < this->max_depth){
            m = choose_playout_move(next_moves, gen);
            this->move(m);
            playout_moves.push_back({m.fin, m.dep});
            if(!(result = check_end(m.fin, current_team)))
                next_moves =this->get_moves(static_cast<TERMINAL_STYLES>(this->b.cases[m.fin.x][m.fin.y].color-16),
                                            current_team);
            else
                next_moves.clear();
            current_team = invert_color(current_team);
            current_depth++;
        }
        std::for_each(playout_moves.crbegin(), playout_moves.crend(),
            [this](Movement m) mutable{ this->move(m); });
        n->victories += result;
        n->n_playouts++;
    }
}

int IA::check_end(coord last_move, TERMINAL_STYLES last_play_team){
    if (last_move.x == static_cast<int>(this->finish[last_play_team])){
        if (last_play_team == this->team) //IA won
            return 1;
        return -1; //IA lost
    }
    return 0; //Game not finished
}

Movement IA::choose_playout_move(std::vector<Movement> &moves, std::mt19937 &gen){
    std::uniform_int_distribution<unsigned int> dis(0,moves.size()-1);
    return moves[dis(gen)];
}