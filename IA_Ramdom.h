//
// ReCreated by Alexis on 19/04/17.
//

#ifndef KAMISADO_IA_H
#define KAMISADO_IA_H


#include <random>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <climits>
#include "Board.h"
#include "Movement.h"
#include "Node.h"

class IA_Ramdom {
public:

    IA_Ramdom();
    void init(const char *file);
    void move(Movement m);
    Movement genmove();

private:
    Board b;
    bool first_move;
    TERMINAL_STYLES team;
    TERMINAL_STYLES next_move_color;

    std::vector<Movement> get_moves(TERMINAL_STYLES color, TERMINAL_STYLES team, bool eval = false) const;
};


#endif //KAMISADO_IA_H