#include <sstream>
#include <iostream>
#include <csignal>
#include "Board.h"
#include "Movement.h"
#include "OtherDisplay.h"
#include <SFML/Graphics.hpp>

void command_input();
//void song();
void nameManager(std::string name1, std::string name2);
void execute_input();
void manage_signals();
static void handler(int signum);
OtherDisplay myDisplay;

int main() {
    manage_signals();
    sf::Thread thread(&command_input);
    thread.launch();
    myDisplay.init();
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
        if(myDisplay.tour)
            myDisplay.tour = 0;
        else
            myDisplay.tour = 1;
        // sf::Thread threadsong(&song);
        // threadsong.launch();
        std::cout << "= \n\n";
    }
    if (command == "endgame"){
        sstream >> myDisplay.val;
    }
}
void command_input(){
    while(1){
        execute_input();
    }
}

// void song(){
//     sf::SoundBuffer buffer;
//     // on charge quelque chose dans le buffer...
//     if(myDisplay.tour == 1){
//         std::cout << "test" << std::endl;
//         buffer.loadFromFile("1.ogg");
//     }
//     else{
//         std::cout << "test0" << std::endl;
//         buffer.loadFromFile("0.ogg");
//     }

//     sf::Sound sound;
//     sound.setBuffer(buffer);
//     sound.play();
// }

// void nameManager(std::string name1, std::string name2){
//     int act = 1;
//     int size = names.size();
//     for(int i = 0; i < size; i++){
//         if (act == 1){
//             if (names[i] != ';'){
//                 myDisplay.name1 = myDisplay.name1 + names[i];
//             }
//             else{
//                 act = 2;
//             }
//         }else{
//             myDisplay.name2 = myDisplay.name2 + names[i];
//         }
//     }
//     std::cout<<myDisplay.name1<<std::endl;
//     std::cout<<myDisplay.name2<<std::endl;
// }

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