#include <sstream>
#include <iostream>
#include <csignal>
#include "Board.h"
#include "Movement.h"
#include "Display.h"
#include <SFML/Graphics.hpp>

void command_input();
//void song();
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
        myDisplay.init();
        std::cout << "= \n\n";
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
        myDisplay.quit();
        exit(EXIT_SUCCESS);
    }
    if (command == "init"){
        myDisplay.init();
        std::cout << "= \n\n";
    }
    if (command == "names"){
        //sstream >> names;
        std::getline(sstream, myDisplay.name1, ';');
        std::getline(sstream, myDisplay.name2);
        std::cout << "= \n\n";
    }
    if (command == "move"){

        Movement m;
        sstream >> m.dep.x;
        sstream >> m.dep.y;
        sstream >> m.fin.x;
        sstream >> m.fin.y;
        myDisplay.b.move(m);
        if(myDisplay.tour){
            myDisplay.sound1.play();
        }
        else{
            myDisplay.sound2.play();
        }
        myDisplay.tour = !myDisplay.tour;
        std::cout << "= \n\n";
    }
    if (command == "endgame"){
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