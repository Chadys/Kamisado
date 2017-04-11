#include "Display.h"

void Display::init(){
    SDL_Init(SDL_INIT_VIDEO);
    fenetre = SDL_CreateWindow(
        "Kamisado façon commercial",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        680,                               // width, in pixels
        680,                               // height, in pixels
        0                  // flags - see below
    );
        if (fenetre == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }
    b.init("./default_board.kms");
}

void Display::GraphBoard(){
    SDL_Rect r;
    int countc, countl;
    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    renderer = SDL_CreateRenderer(fenetre, -1, 0);
    // Select the color for drawing. It is set to red here.
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(renderer);
    
    SDL_SetRenderDrawColor(renderer, 84, 69, 67, 255);
    r.x = 25;
    r.y = 25;
    r.w = 630;
    r.h = 630;
    SDL_RenderFillRect(renderer, &r);
    //SDL_RenderPresent(renderer);
    
    SDL_SetRenderDrawColor(renderer, 200, 173, 127, 255);
    r.x = 57;
    r.y = 57;
    r.w = 566;
    r.h = 566;
    SDL_RenderFillRect(renderer, &r);
    //SDL_RenderPresent(renderer);
    
    if (tour == 1)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    r.x = 60;
    r.y = 60;
    r.w = 560;
    r.h = 560;
    SDL_RenderFillRect(renderer, &r);
    //SDL_RenderPresent(renderer);

    countc = 0;
    for(auto &row : b.cases){
        countl = 0;
        for (const Case &c : row) {
            if (c.color == BG_CYAN)
                SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
            else if (c.color == BG_BLUE)
                SDL_SetRenderDrawColor(renderer, 0, 47, 167, 255);
            else if (c.color == BG_PURPLE)
                SDL_SetRenderDrawColor(renderer, 139, 105, 180, 255);
            else if (c.color == BG_MAGENTA)
                SDL_SetRenderDrawColor(renderer, 252, 138, 233, 255);
            else if (c.color == BG_YELLOW)
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            else if (c.color == BG_RED)
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            else if (c.color == BG_GREEN)
                SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255);
            else if (c.color == BG_BROWN)
                SDL_SetRenderDrawColor(renderer, 160, 82, 45, 255);
            else
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            r.x = 62 + (70*countl);
            r.y = 62 + (70*countc);
            r.w = 66;
            r.h = 66;
            SDL_RenderFillRect(renderer, &r);
            //SDL_RenderPresent(renderer);
            if(c.pion != nullptr){
                if(c.pion->team == BLACK)
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                else if (c.pion->team == WHITE)
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                r.x = 70 + (70*countl);
                r.y = 70 + (70*countc);
                r.w = 50;
                r.h = 50;
                SDL_RenderFillRect(renderer, &r);
                //SDL_RenderPresent(renderer);
                r.x = 75 + (70*countl);
                r.y = 75 + (70*countc);
                r.w = 40;
                r.h = 40;

                if (c.pion->color == CYAN)
                    SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
                else if (c.pion->color == BLUE)
                    SDL_SetRenderDrawColor(renderer, 0, 47, 167, 255);
                else if (c.pion->color == PURPLE)
                    SDL_SetRenderDrawColor(renderer, 139, 105, 180, 255);
                else if (c.pion->color == MAGENTA)
                    SDL_SetRenderDrawColor(renderer, 252, 138, 233, 255);
                else if (c.pion->color == YELLOW)
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                else if (c.pion->color == RED)
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                else if (c.pion->color == GREEN)
                    SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255);
                else if (c.pion->color == BROWN)
                    SDL_SetRenderDrawColor(renderer, 160, 82, 45, 255);
                else
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &r);
                //SDL_RenderPresent(renderer);
            }
            countl ++;
        }
        countc ++;
    }
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(fenetre);
    SDL_DestroyRenderer(renderer);
}

void Display::test(){
    SDL_PollEvent(NULL);
}

void Display::quit(){
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}