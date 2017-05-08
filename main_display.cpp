#include <sstream>
#include <iostream>
#include <csignal>
#include "Board.h"
#include "Display.h"

void command_input();
bool execute_input();
void manage_signals();
static void handler(int signum);
Display myDisplay;

int main() {
    manage_signals();
    std::string line, command, names;
    std::getline(std::cin, line); 
    std::istringstream sstream(line);
    sstream >> command;
    sf::Thread thread(&command_input);
    if (command == "init"){
        thread.launch();
        std::cout << "= \n\n";
        myDisplay.init();
    }
    thread.wait();
    return 0;
}


bool execute_input(){
    std::string line, command, names;
    std::getline(std::cin, line); 
    std::istringstream sstream(line);
    sstream >> command;
    if (command == "quit") {
        std::cout << "= \n\n";
        for (int i = 0; i < 4; ++i) {
            myDisplay.sounds[i].stop();
        }
        myDisplay.quit();
        exit(EXIT_SUCCESS);
        return true;

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
        return false;
    }
    else if (command == "move"){
        Movement m;
        sstream >> m.dep.x;
        sstream >> m.dep.y;
        sstream >> m.fin.x;
        sstream >> m.fin.y;
        myDisplay.move(m);
        std::cout << "= \n\n";
        return false;
    }
    else if (command == "genmove"){
        myDisplay.humanMove = 1;
        while(!myDisplay.iFinish){
        }
        myDisplay.iFinish = 0;
        std::cout << "= " << myDisplay.m << "\n\n"; 
        return false;
    }
    else if (command == "endgame"){
        sstream >> myDisplay.val;
        myDisplay.sounds[2].play();
        std::cout << "= \n\n";
        return false;
    }
    return false;
}

void command_input(){
    bool endThread = 0;
    while(!endThread){
        endThread = execute_input();
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