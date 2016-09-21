#ifndef _GAMEOFLIFE
#define _GAMEOFLIFE

#include <string>
#include <vector>

class GameOfLife
{
    public:
    GameOfLife(int size);
    ~GameOfLife();
    void Play();
    void PrintBoard();
    void LoadFile(std::string filename);
    void LoadRandom();
    unsigned int max_gen;

    private:
    int CountNeighbors(int x, int y);

    std::vector<std::vector<int>> space;
    int space_size;
    
};

#endif
