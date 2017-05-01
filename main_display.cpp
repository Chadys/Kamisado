#include <sstream>
#include <iostream>
#include <csignal>
#include "Board.h"
#include "Movement.h"
#include "Display.h"
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

void command_input();
void nameManager(std::string name1, std::string name2);
void execute_input();
void manage_signals();
static void handler(int signum);
Display myDisplay;

int main() {
    manage_signals();
    std::string line, command, names;
    std::getline(std::cin, line); 
    std::istringstream sstream(line);
    sstream >> command;
    if (command == "init"){
        sf::Thread thread(&command_input);
        thread.launch();
        std::cout << "= \n\n";
        myDisplay.init();
    }
    return 0;
}


void execute_input(){
    std::string line, command, names;
    std::getline(std::cin, line); 
    std::istringstream sstream(line);
    sstream >> command;
    if (command == "quit") {
        std::cout << "= \n\n";
        myDisplay.sound1.stop();
        myDisplay.sound2.stop();
        myDisplay.sound3.stop();
        myDisplay.sound4.stop();
        myDisplay.quit();
        exit(EXIT_SUCCESS);
    }
    if (command == "names"){
        std::getline(sstream, myDisplay.name1, ';');
        std::getline(sstream, myDisplay.name2);
        if(myDisplay.name1 == " Im Different"){
            myDisplay.player1isdifferent = 1;
        }
        if(myDisplay.name2.find("Im Different")!= std::string::npos){
            myDisplay.player2isdifferent = 1;
        }
        std::cout << "= \n\n";
    }
    else if (command == "move"){
        Movement m;
        sstream >> m.dep.x;
        sstream >> m.dep.y;
        sstream >> m.fin.x;
        sstream >> m.fin.y;
        myDisplay.b.move(m);
        if(myDisplay.tour && myDisplay.player1isdifferent){
            myDisplay.sound4.play();
        }
        else if(myDisplay.tour){
            myDisplay.sound1.play();
        }        
        else if(!myDisplay.tour && myDisplay.player2isdifferent){
            myDisplay.sound4.play();
        }
        else{
            myDisplay.sound2.play();
        }
        myDisplay.tour = !myDisplay.tour;
        std::cout << "= \n\n";
    }
    else if (command == "genmove"){
        myDisplay.humanMove = 1;
        while(!myDisplay.iFinish){
        }
        myDisplay.iFinish = 0;
        std::cout << "= " << myDisplay.m << "\n\n"; 
    }
    else if (command == "endgame"){
        sstream >> myDisplay.val;
        myDisplay.sound3.play();
        std::cout << "= \n\n";
    }
}
void command_input(){
    while(1){
        execute_input();
    }
}

void manage_signals(){
    struct sigaction sa;
    sa.sa_handler = handler;
    if ((sigaction(SIGABRT, &sa, NULL) == -1) |
        (sigaction(SIGFPE, &sa, NULL) == -1) |
        (sigaction(SIGILL, &sa, NULL) == -1) |
        (sigaction(SIGINT, &sa, NULL) == -1) |
        (sigaction(SIGSEGV, &sa, NULL) == -1) |
        (sigaction(SIGTERM, &sa, NULL) == -1) |
        (sigaction(SIGBUS, &sa, NULL) == -1) |
        (sigaction(SIGPIPE, &sa, NULL) == -1) |
        (sigaction(SIGQUIT, &sa, NULL) == -1) |
        (sigaction(SIGSYS, &sa, NULL) == -1)){}
}

inline void handler(int sig)
{
    std::cout << "= ?\n\n";
    signal(sig, SIG_DFL);
    raise(sig);
    return;
}