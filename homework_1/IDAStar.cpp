#include "IDAStar.h"
#include "BoardWithTiles.h"

#include <iostream>
#include <limits.h>
#include <map>

IDAStar::IDAStar(BoardWithTiles start, BoardWithTiles target) 
{
    this->start = start;
    this->target = target;
    this->bound = start.getManhattan(target);
                                            
}

int IDAStar::search(int countLevels, std::stack<BoardWithTiles> &path) 
{ 
    BoardWithTiles current = path.top(); 
    int wayEstimation = countLevels + current.getManhattan(target); 
    if (wayEstimation > bound) 
    {
        return wayEstimation;
    }
    if (current == target) 
    {
        return 0; 
    }

    int minEstimation = INT_MAX; 
    std::priority_queue<BoardWithTiles> neighbours = current.getNeighbours(); 
    while (!neighbours.empty()) 
    { 
        BoardWithTiles next = neighbours.top(); 
        neighbours.pop(); 

        path.push(next); 
        int nextEstimation = search(countLevels + 1, path); 
        if (nextEstimation == 0)
        {
            return 0;    
        }
        minEstimation = std::min(nextEstimation, minEstimation);

        path.pop();
    }
    return minEstimation;
}

void IDAStar::printPath()
{
    std::cout << "--------\nPath:\n";
    std::map<char, std::string> label = 
    {
        {'u', "up"},
        {'d', "down"},
        {'l', "left"},
        {'r', "right"},
        {'-', "root"},
    };

    std::stack<std::string> moves;
    while(!targetPath.empty())
    {
        moves.push(label[targetPath.top().getTrail()]);
        targetPath.pop();
    }

    while(!moves.empty())
    {
        std::cout << " " << moves.top() << std::endl;
        moves.pop();
    }
    std::cout << "Moves: " << bound << std::endl;
}

void IDAStar::findPath() 
{
    std::stack<BoardWithTiles> path; 
    path.push(start); 

    while(true) 
    {
        int newBound = search(0, path); 
        if(newBound == 0) 
        {
            targetPath = path; 
            return;    
        }
        bound = newBound;
    }
}