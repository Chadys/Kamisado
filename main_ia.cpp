//
// Created by julie on 07/04/17.
//

#include <sstream>
#include <iostream>
#include <csignal>
#include "IA.h"

void command_input(IA ia);
static void manage_signals();
static void handler(int signum);

int main() {
    IA ia;
    manage_signals();
    command_input(ia);
    return 0;
}

void command_input(IA ia){
    std::string line, command;
    bool init_done = false;

    while (std::getline(std::cin, line)){ //wait for user input
        std::istringstream sstream(line);
        sstream >> command;
        if (command == "quit") {
            std::cout << "= \n\n";
            return;
        }
        if (command == "init"){
            if(!init_done) {
                ia.init("./default_board.kms");
                init_done = true;
                std::cout << "= \n\n";
                continue;
            }
        }
        if (command == "name"){
            std::cout << "= Yolo\n\n";
            continue;
        }
        if(init_done){
            if (command == "move"){
                    Movement m;
                    sstream >> m.dep.x;
                    sstream >> m.dep.y;
                    sstream >> m.fin.x;
                    sstream >> m.fin.y;
                    ia.move(m);
                    std::cout << "= \n\n";
                    continue;
            }
            if (command == "genmove"){
                Movement m = ia.genmove();
                std::cout << "= " << m << "\n\n";
                continue;
            }
        }
        std::cout << "= ?\n\n";
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