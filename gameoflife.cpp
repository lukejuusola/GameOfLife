#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <random>
#include <cmath>
#include <time.h>
#include "gameoflife.h"

GameOfLife::GameOfLife(int size)
{
    if(size < 0)
        throw std::invalid_argument("Size must be non-negative");
    space_size = size;
    for(int i = 0; i < size; i++)
    {
        std::vector<int> v;
        space.push_back(v);
        for(int j = 0; j < size; j++)
            space[i].push_back(0);
    }
    max_gen = 0;
    std::cout << "Game Of Life initialized" << std::endl;
}

GameOfLife::~GameOfLife()
{
}

void GameOfLife::LoadFile(std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    int lineno = 0;
    if(file.is_open())
    {
        while(std::getline(file, line) and lineno < 20)
        {
            for(int i = 0; i < space_size and i < line.size(); i++)
            {
                if(line[i] == '1')
                    space[lineno][i] = 1;
                else 
                    space[lineno][i] = 0;
            }
            lineno++;
        }
        file.close();
        while(lineno < 20)
        {
            for(int i = 0; i < space_size; i++)
                for(int j = 0; j < space_size; j++)
                    space[i][j] = 0;
        }
    }
    //else 
    //  throw std::exception("File could not be opened");
}

void GameOfLife::LoadRandom()
{
    std::default_random_engine gen(time(NULL));
    std::uniform_real_distribution<double> dist(0.0,1.0);
    for(int i = 0; i < space_size; i++)
        for(int j = 0; j < space_size; j++)
            space[i][j] = round(dist(gen));
}
void GameOfLife::Play()
{
    std::cout << "Playing" << std::endl;
    unsigned int cur_gen = 0;
    while(cur_gen <= max_gen)
    {    
        if(cur_gen != 0)
        {
            // Find next board
            std::vector<std::vector<int>> new_space (space_size, std::vector<int>(space_size));
        
            for(int x = 0; x < space_size; x++)
            {
                // Update square in new space
                for(int y = 0; y < space_size; y++)
                {
                    int neighbor_count = CountNeighbors(x, y);
                    switch(neighbor_count)
                    {
                    case 2: 
                        new_space[x][y] = space[x][y];
                        break;
                    case 3:
                        new_space[x][y] = 1;
                        break;
                    default:
                        new_space[x][y] = 0;
                    }
                }
            }
        
            // Copy next board onto current board
            for(int i = 0; i < space_size; i++)
                for(int j = 0; j < space_size; j++)
                    space[i][j] = new_space[i][j];
        }
        system("clear");
        PrintBoard();
        std::cout << "Generation Number: " << cur_gen << std::endl;
        cur_gen++;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int GameOfLife::CountNeighbors(int x, int y)
{
    int upper_x, lower_x, upper_y, lower_y;
    // x bounds
    if(x == 0)
    {
        lower_x = 0;
        upper_x = 1;
    }
    else if(x == space_size-1)
    {
        lower_x = -1;
        upper_x = 0;
    }
    else if(x > 0 and x < space_size - 1)
    {
        lower_x = -1;
        upper_x = 1;
    }
    else // oob
    {
        return 0;
    }

    // y bounds
    if(y == 0)
    {
        lower_y = 0;
        upper_y = 1;
    }
    else if(y == space_size-1)
    {
        lower_y = -1;
        upper_y = 0;
    }
    else if(y > 0 and y < space_size - 1)
    {
        lower_y = -1;
        upper_y = 1;
    }
    else // oob
    {
        return 0;
    }
    
    std::vector< std::pair<int, int> > potential_neighbors;
    // valid adjacent squares
    for(int i = lower_x; i <= upper_x; i++)
    {
        for(int j = lower_y; j <= upper_y; j++)
        {
            if(i == 0 and j == 0)
                continue;
            potential_neighbors.push_back(std::pair<int, int>(x+i, y+j));
        }
    }
    // count
    int neighbor_count = 0;
    for(int i = 0; i < potential_neighbors.size(); i++)
    {
        if(space[potential_neighbors[i].first][potential_neighbors[i].second] == 1)
            neighbor_count++;
    }
    return neighbor_count;
}

void GameOfLife::PrintBoard()
{
    for(int i = 0; i < space_size; i++)
    {
        for(int j = 0; j < space_size; j++)
        {
            int square = space[i][j];
            if(square == 1)
                std::cout << "0";
            else 
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}
