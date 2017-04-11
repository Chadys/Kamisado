//
// Created by Alexis on 10/04/17.
//

#ifndef KAMISADO_DISPLAY_H
#define KAMISADO_DISPLAY_H

#include "Case.h"
#include "Board.h"
#include "Pion.h"
#include "SDL2/SDL.h"

class Display {
public:
    Board b;
    int tour = 1;
    void quit();
    void init();
    void test();
    void GraphBoard();
private:
    SDL_Window *fenetre;
    SDL_Renderer* renderer;
};

#endif //KAMISADO_DISPLAY_H