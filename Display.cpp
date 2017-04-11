#include "Display.h"

void Display::init(){
    SDL_Init(SDL_INIT_VIDEO);
    fenetre = SDL_CreateWindow(
        "Kamisado façon commercial",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        680,                               // width, in pixels
        680,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );
        if (fenetre == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }
    b.init("./default_board.kms");
}

void Display::GraphBoard(){
    SDL_Renderer* renderer;
    SDL_Rect r;
    int countc, countl;
    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    renderer = SDL_CreateRenderer(fenetre, -1, 0);
    // Select the color for drawing. It is set to red here.
    SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(renderer);
    
    SDL_SetRenderDrawColor(renderer, 153, 81, 43, 255);
    r.x = 25;
    r.y = 25;
    r.w = 630;
    r.h = 630;
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);
    
    SDL_SetRenderDrawColor(renderer, 200, 173, 127, 255);
    r.x = 57;
    r.y = 57;
    r.w = 566;
    r.h = 566;
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);
    
    if (tour == 1)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    r.x = 60;
    r.y = 60;
    r.w = 560;
    r.h = 560;
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);

    countc = 0;
    for(auto &row : b.cases){
        countl = 0;
        for (const Case &c : row) {
            if (c.color == BG_CYAN)
                 SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
            else
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            r.x = 62 + (70*countl);
            r.y = -800 + (70*countc);
            r.w = 66;
            r.h = 66;
            SDL_RenderFillRect(renderer, &r);
            SDL_RenderPresent(renderer);
            countl ++;
        }
        countc ++;
    }


}

void Display::quit(){
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}