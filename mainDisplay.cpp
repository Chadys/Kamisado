#include <sstream>
#include <iostream>
#include <csignal>
#include "Board.h"
#include "Display.h"

void command_input(Display myDisplay);
static void manage_signals();
static void handler(int signum);

int main() {
    Display myDisplay;
    command_input(myDisplay);
    return 0;
}

void command_input(Display myDisplay){
    std::string line, command;

    manage_signals();
    while (std::getline(std::cin, line)){ //wait for user input
        std::istringstream sstream(line);
        sstream >> command;
        if (command == "quit") {
            std::cout << "= \n\n";
            myDisplay.quit();
            exit(EXIT_SUCCESS);
        }
        if (command == "init"){
            std::cout << "Create Window\n";
            myDisplay.b.init("./default_board.kms");
            myDisplay.init();
            myDisplay.GraphBoard();
            std::cout << "= \n\n";
            continue;
        }
        if (command == "name"){
            std::cout << "= Yolo\n\n";
            continue;
        }
        if (command == "move"){
            Movement m;
            sstream >> m.dep.x;
            sstream >> m.dep.y;
            sstream >> m.fin.x;
            sstream >> m.fin.y;
            std::cout << "= \n\n";
            continue;
        }
        if (command == "genmove"){
            continue;
        }
    }
}

void manage_signals(){
    struct sigaction sa;
    sa.sa_handler = handler;
    if (sigaction(SIGABRT, &sa, NULL) == -1 |
        sigaction(SIGFPE, &sa, NULL) == -1 |
        sigaction(SIGILL, &sa, NULL) == -1 |
        sigaction(SIGINT, &sa, NULL) == -1 |
        sigaction(SIGSEGV, &sa, NULL) == -1 |
        sigaction(SIGTERM, &sa, NULL) == -1 |
        sigaction(SIGBUS, &sa, NULL) == -1 |
        sigaction(SIGKILL, &sa, NULL) == -1 |
        sigaction(SIGPIPE, &sa, NULL) == -1 |
        sigaction(SIGQUIT, &sa, NULL) == -1 |
        sigaction(SIGSYS, &sa, NULL) == -1);
}

inline void handler(int sig)
{
    std::cout << "= ?\n\n";
    signal(sig, SIG_DFL);
    raise(sig);
    return;
}