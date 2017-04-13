//
// Created by Alexis on 12/04/17.
//

#ifndef KAMISADO_OTHERDISPLAY_H
#define KAMISADO_OTHERDISPLAY_H

#include "Case.h"
#include "Board.h"
#include "Pion.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class OtherDisplay {
public:
    std::string val = "";
    Board b;
    int tour = 1;
    std::string name1 = "";
    std::string name2 = "";
    void quit();
    void init();
    //void song();
    //void test();
    void GraphBoard();
private:
     sf::RenderWindow window;
};

#endif //KAMISADO_OTHERDISPLAY_H