#include <iostream>
#include <string>
#include "gameoflife.h"

int main(int argc, char* argv[])
{
    std::string filename, updaterules;
    bool random_flag = false;
    switch(argc)
    {
    case 3:
        updaterules = argv[2];
    case 2: 
        filename = argv[1];
        break;
    default:
        std::cout << "GameOfLife <filename> [update-rules]" << std::endl;
        std::cout << "GameOfLife RANDOM" << std::endl;
        return 0;
    }
    GameOfLife gol(20);
    if(filename == "RANDOM")
        gol.LoadRandom();
    else
        gol.LoadFile(filename);
    
    gol.max_gen = 500;
    gol.Play();
    return 0;
}
