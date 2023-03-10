#include <iostream>
#include <vector>
#include <chrono>

#include "IDAStar.h"

BoardWithTiles initStart(int size)
{
    std::cout << "Enter board: " << std::endl; 
    std::vector<int> tiles; 
    for(int i = 0; i <= size; ++i) 
    {
        int tile;
        std::cin >> tile; 
        tiles.push_back(tile); 
    }
    return BoardWithTiles(tiles); 
}

BoardWithTiles initTarget(int size, int emptyTileInTarget) 
{
    std::vector<int> targetTiles; 
    for(int i = 0; i < size; ++i) 
    {
        if(i == emptyTileInTarget) 
        {
            targetTiles.push_back(0); 
        }
        targetTiles.push_back(i + 1); 
    }
    if(emptyTileInTarget == 8 || emptyTileInTarget == -1) 
    {
        targetTiles.push_back(0); 
    }
    return BoardWithTiles(targetTiles); 
}

int main()
{
    int size, emptyTileTarget; 
    std::cout << "N = "; 
    std::cin >> size; 
    std::cout << "Empty tile in goal = ";
    std::cin >> emptyTileTarget; 

    BoardWithTiles start = initStart(size), 
                   target = initTarget(size, emptyTileTarget); 

    IDAStar idaStar(start, target); 
    auto startTime = std::chrono::high_resolution_clock::now(); 
    idaStar.findPath(); 
    auto endTime = std::chrono::high_resolution_clock::now(); 

    idaStar.printPath(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime); 
    std::cout << "Time for execution: " << (double)(duration.count()) / 1000 << "s" << std::endl; 
    return 0;
}