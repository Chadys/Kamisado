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
    bool player1isdifferent;
    bool player2isdifferent;
    bool iFinish;
    bool humanMove;
    Movement m;
    std::string val;
    sf::Sound sounds[4];
    std::string name1;
    std::string name2;

    Display();
    void quit();
    void init();
    void GraphBoard();
    void move(Movement m);

private:
    struct Rotation{
        float angle;
        float speed;
        Rotation(float a, float s) : angle(a), speed(s) {}
    };
    sf::RenderWindow window;
    bool someOneSelected;
    bool firstMove;
    coord coord_S;
    unsigned int tailleWin;
    short win_text_increment;
    Board b;
    bool tour;
    Rotation rotation_victory;
    Rotation rotation_selected;

    void updateSelected(int x, int y);
};

#endif //KAMISADO_DISPLAY_H