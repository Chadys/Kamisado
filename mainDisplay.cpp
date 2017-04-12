#include <sstream>
#include <iostream>
#include <csignal>
#include "SDL2/SDL.h"
#include "Board.h"
#include "Display.h"
#include <ctime>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void command_input();
void manage_signals();
static void handler(int signum);
static void print(const boost::system::error_code&);
static void GraphBoardEv();
Display myDisplay;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    manage_signals();
    // boost::asio::io_service io;
    // boost::asio::deadline_timer t(io, boost::posix_time::seconds(3));
    // t.async_wait(&print);
    // io.run();
    command_input();
    return 0;
}

void print(const boost::system::error_code&)
{
    command_input();
    std::cout << "UGH" << std::endl;
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    t.async_wait(&print);
    io.run();
}

void GraphBoardEv(){
    SDL_Event evenements;
    while(1){
        SDL_PollEvent(&evenements);
        if(evenements.type == SDL_QUIT){
            myDisplay.quit();
            exit(EXIT_SUCCESS);
        }
    }
}

void command_input(){

    std::string line, command;
    std::getline(std::cin, line); 
    std::istringstream sstream(line);
    sstream >> command;
    if (command == "quit") {
        std::cout << "= \n\n";
        myDisplay.quit();
        exit(EXIT_SUCCESS);
    }
    if (command == "init"){
        std::cout << "Create Window\n";
        myDisplay.init();
        myDisplay.GraphBoard();
        myDisplay.test();
        std::cout << "= \n\n";
    }
    if (command == "name"){
        std::cout << "= Yolo\n\n";
    }
    if (command == "move"){
        Movement m;
        sstream >> m.dep.x;
        sstream >> m.dep.y;
        sstream >> m.fin.x;
        sstream >> m.fin.y;
        myDisplay.b.move(m);
        myDisplay.GraphBoard();
        myDisplay.test();
        myDisplay.b.print();
        std::cout << "= \n\n";
    }
    if (command == "genmove"){
        myDisplay.test();
    }
    else{
        myDisplay.test();
        std::cout<<"test\n";
    }
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    t.async_wait(&print);
    io.run();
        myDisplay.GraphBoard();
    
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