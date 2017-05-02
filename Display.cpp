#include "Display.h"

Display::Display() : player1isdifferent(false), player2isdifferent(false), iFinish(false), humanMove(false), val(""),
                     name1(""), name2(""), someOneSelected(false), firstMove(true), tailleWin(70), win_text_increment(1),
                     tour(true), rotation_victory({0.0f, 0.0f}), rotation_selected({0.0, 0.5}){}

void Display::init(){
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    this->window.create(sf::VideoMode(680, 680), "Kamisado non Commercial", sf::Style::Close, settings);
    b.init("./default_board.kms");
    sf::SoundBuffer buffer1;
    sf::SoundBuffer buffer2;
    sf::SoundBuffer buffer3;
    sf::SoundBuffer buffer4;

    buffer1.loadFromFile("./Extras/0Ampl.ogg");
    buffer2.loadFromFile("./Extras/1Ampl.ogg");
    buffer3.loadFromFile("./Extras/LaughSong.ogg");
    buffer4.loadFromFile("./Extras/diff.ogg");

    this->sounds[0].setBuffer(buffer1);
    this->sounds[1].setBuffer(buffer2);
    this->sounds[2].setBuffer(buffer3);
    this->sounds[3].setBuffer(buffer4);

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (this->window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    if(humanMove == 1){
                            if(someOneSelected == 0 && event.mouseButton.x < 609 && event.mouseButton.y < 609 && event.mouseButton.x > 71 && event.mouseButton.y > 71 && this->firstMove){
                                this->coord_S = {(event.mouseButton.x-70)/70, (event.mouseButton.y-70)/70};
                                if(b.cases[coord_S.y][coord_S.x].pion != nullptr)
                                    someOneSelected = 1;
                            }
                            else if(someOneSelected == 1){
                                m.dep.x = this->coord_S.y;
                                m.dep.y = this->coord_S.x;
                                m.fin.x = (event.mouseButton.y-70)/70;
                                m.fin.y = (event.mouseButton.x-70)/70;
                                someOneSelected = 0;
                                humanMove = 0;
                                iFinish = 1;                        
                            }
                    }
                }
                if (event.mouseButton.button ==sf::Mouse::Right && firstMove){
                    someOneSelected = 0;
                    this->coord_S = {9, 9};
                }
            }
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                this->window.close();
        }
        this->window.clear(sf::Color(20, 20, 20));
        GraphBoard();
        this->window.display();
    }
}

void Display::GraphBoard(){
    if(rotation_victory.angle > 360){
        rotation_victory.angle = 0;
    }
    if(rotation_selected.angle > 360){
        rotation_selected.angle = 0;
    }
    int countl, countc;
    sf::Font font;
    font.loadFromFile("./Extras/Japanese.ttf");
    sf::Text t;
    t.setFont(font);
    t.setString(L"w");

    sf::Font font2;
    font2.loadFromFile("./Extras/UbuntuMono-B.ttf");
    sf::Text t2;
    sf::Text t3;
    t2.setFont(font2);
    t2.setString(name1);
    t3.setFont(font2);
    t3.setString(name2);
    t2.setCharacterSize(24);
    t3.setCharacterSize(24);
    t2.setColor(sf::Color::Black);
    t3.setColor(sf::Color::White);

    sf::CircleShape shape(25, 6);
    shape.setOutlineThickness(3);

    sf::RectangleShape r(sf::Vector2f(630, 630));
    r.setPosition(25, 25);
    r.setFillColor(sf::Color(84, 69, 67));
    this->window.draw(r);

    t2.setPosition(25, 20);
    this->window.draw(t2);

    t3.setPosition(680-37-t3.getLocalBounds().width, 625);
    this->window.draw(t3);


    r.setSize(sf::Vector2f(566, 566));
    r.setPosition(57, 57);
    r.setFillColor(sf::Color(200, 173, 127));
    this->window.draw(r);

    r.setSize(sf::Vector2f(560, 560));
    r.setPosition(60, 60);
    r.setFillColor(sf::Color(0, 0, 0));
    this->window.draw(r);
    
    countc = 0;
    for(auto &row : b.cases){
        countl = 0;
        for (const Case &c : row) {
            if (c.color == BG_CYAN)
                r.setFillColor(sf::Color(255, 140, 0, 255));
            else if (c.color == BG_BLUE)
                r.setFillColor(sf::Color(30, 100, 250, 255));
            else if (c.color == BG_PURPLE)
                r.setFillColor(sf::Color(139, 105, 180, 255));
            else if (c.color == BG_MAGENTA)
                r.setFillColor(sf::Color(252, 138, 233, 255));
            else if (c.color == BG_YELLOW)
                r.setFillColor(sf::Color(255, 255, 0, 255));
            else if (c.color == BG_RED)
                r.setFillColor(sf::Color(255, 0, 0, 255));
            else if (c.color == BG_GREEN)
                r.setFillColor(sf::Color(50, 205, 50, 255));
            else if (c.color == BG_BROWN)
                r.setFillColor(sf::Color(160, 82, 45, 255));
            else
                r.setFillColor(sf::Color(0, 0, 0, 255));
            r.setPosition(62 + (70*countl), 62 + (70*countc));
            r.setSize(sf::Vector2f(66, 66));
            this->window.draw(r);
            shape.setRotation(90);
            if(c.pion != nullptr){
                if(c.pion->team == BLACK){
                    shape.setOutlineColor(sf::Color(0, 0, 0, 255));
                    shape.setFillColor(sf::Color(50, 50, 50, 255));
                    shape.rotate(this->rotation_victory.angle += this->rotation_victory.speed);

                }
                else if (c.pion->team == WHITE){
                    shape.setOutlineColor(sf::Color(255, 255, 255, 255));
                    shape.setFillColor(sf::Color(220, 220, 220, 255));
                    shape.rotate(360 - (this->rotation_victory.angle += this->rotation_victory.speed));
                }
                if(this->coord_S.y == countc && this->coord_S.x == countl && someOneSelected == 1){
                    shape.rotate(rotation_selected.angle += rotation_selected.speed);
                }
                shape.setPosition(45+50 + (70*countl), 95 + (70*countc));



                if (c.pion->color == CYAN)
                    t.setColor(sf::Color(200, 100, 0, 255));
                else if (c.pion->color == BLUE)
                    t.setColor(sf::Color(20, 40, 170, 255));
                else if (c.pion->color == PURPLE)
                    t.setColor(sf::Color(100, 80, 160, 255));
                else if (c.pion->color == MAGENTA)
                    t.setColor(sf::Color(200, 120, 210, 255));
                else if (c.pion->color == YELLOW)
                    t.setColor(sf::Color(200, 200, 0, 255));
                else if (c.pion->color == RED)
                    t.setColor(sf::Color(200, 0, 0, 255));
                else if (c.pion->color == GREEN)
                    t.setColor(sf::Color(20, 150, 20, 255));
                else if (c.pion->color == BROWN)
                    t.setColor(sf::Color(130, 50, 30, 255));
                else
                    t.setColor(sf::Color(0, 0, 0, 255));
                sf::FloatRect textRect2 = shape.getLocalBounds();
                shape.setOrigin(textRect2.left + textRect2.width/2.0f,textRect2.top  + textRect2.height/2.0f);
                this->window.draw(shape);
                t.setPosition(70+14 + (70*countl), 72 + (70*countc)); 
                this->window.draw(t);  
            }
            countl ++;
        }
        countc ++;
    }

    sf::Text tv;
    tv.setFont(font2);
    tv.setString(name1);
    if(tailleWin < 70 || tailleWin > 80)
        win_text_increment = -win_text_increment;
    tv.setCharacterSize(tailleWin += win_text_increment);
    tv.setColor(sf::Color::White);
    
    if(val == "0"){
        tv.setString(name1);
        sf::FloatRect textRect = tv.getLocalBounds();
        tv.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
        tv.setPosition(sf::Vector2f(340, 310));
        this->window.draw(tv);
        tv.setString("Won !");
        textRect = tv.getLocalBounds();
        tv.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
        tv.setPosition(sf::Vector2f(340, 370));
        this->window.draw(tv);
        if(rotation_victory.speed < 2)
            rotation_victory.speed += 0.0001;
    }
    else if(val == "1"){
        tv.setString(name2);
        sf::FloatRect textRect = tv.getLocalBounds();
        tv.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
        tv.setPosition(sf::Vector2f(340, 310));
        this->window.draw(tv);
        tv.setString("Won !");
        textRect = tv.getLocalBounds();
        tv.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
        tv.setPosition(sf::Vector2f(340, 370));
        this->window.draw(tv);
        if(this->rotation_victory.speed < 2)
            this->rotation_victory.speed += 0.0001;
    }

}

void Display::move(Movement m){
    this->b.move(m);
    if(this->tour){
        if(this->player1isdifferent)
            this->sounds[3].play();
        else
            this->sounds[0].play();
    }
    else{
        if(this->player2isdifferent)
            this->sounds[3].play();
        else
            this->sounds[1].play();
    }
    this->tour = !this->tour;
    this->firstMove = false;
    this->updateSelected(m.fin.x, m.fin.y);
}

void Display::quit(){
    this->window.close();
}

void Display::updateSelected(int x, int y){
    TERMINAL_STYLES color = static_cast<TERMINAL_STYLES>(this->b.cases[x][y].color - 16);
    for(Pion *pion : this->b.pions){
        //std::cout << color << " " << pion->color << std::endl;
        if(color==pion->color && b.cases[x][y].pion->team != pion->team){
            coord_S = {pion->pos.y, pion->pos.x};
            //std::cout << "now the selected is : " << coord_S.x << " " << coord_S.y << std::endl;
            someOneSelected = true;
            break;
        }
    }
}

