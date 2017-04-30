//
// Created by Alexis on 12/04/17.
//

#ifndef KAMISADO_DISPLAY_H
#define KAMISADO_DISPLAY_H

#include "Case.h"
#include "Board.h"
#include "Pion.h"
#include "Movement.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Display {
public:
    Movement m;
    sf::Sound sound1;
    sf::Sound sound2;
    sf::Sound sound3;
    sf::Sound sound4;
    std::string val = "";
    bool humanMove = 0;
    bool firstMove = 1;
    bool someOneSelected = 0;
    bool OMGHEISHERE = 0;
    int xS;
    int yS;
    int tailleWin = 70;
    int ugh = 1;
    Board b;
    bool tour = true;
    std::string name1 = "";
    std::string name2 = "";
    void quit();
    void init();
    void GraphBoard();
private:
     sf::RenderWindow window;
     float rotate = 0;
     float rotateS = 0;
     float rot = 0;
     float rotS = 0.5;
};

#endif //KAMISADO_DISPLAY_H