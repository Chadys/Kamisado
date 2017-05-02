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
    sf::Sound sounds[4];
    bool player1isdifferent;
    bool player2isdifferent;
    std::string val;
    bool iFinish;
    bool humanMove;
    bool someOneSelected;
    bool firstMove;
    coord coord_S;
    unsigned int tailleWin;
    short win_text_increment;
    Board b;
    bool tour;
    std::string name1;
    std::string name2;

    Display();
    void quit();
    void init();
    void GraphBoard();
    void updateSelected(int x, int y);
private:
    struct Rotation{
        float angle;
        float speed;
        Rotation(float a, float s) : angle(a), speed(s) {}
    };
    sf::RenderWindow window;
    Rotation rotation_victory;
    Rotation rotation_selected;
};

#endif //KAMISADO_DISPLAY_H