#include "BoardWithTiles.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>

BoardWithTiles::BoardWithTiles(){}

BoardWithTiles::BoardWithTiles(std::vector<int> tiles)
{
    this->tiles = tiles;
    this->sizeBoard = sqrt(tiles.size()); 
    this->tileEmpty = findPos(0);
    this->manhattanDist = -1;
    trail = '-';
}

int BoardWithTiles::getTileEmpty()
{
    return tileEmpty;
}

char BoardWithTiles::getTrail()
{
    return trail;
}

int BoardWithTiles::manhattan(BoardWithTiles target)
{
    int manhattanDist = 0;
    int tileSize = tiles.size();
    for(int i = 0; i < tileSize; ++i)
    {
        if(tiles[i] == 0)
        {
            continue; 
        }
        int indexOnTileInTargetBoard = target.findPos(tiles[i]);
        int targetR = indexOnTileInTargetBoard / sizeBoard;
        int targetC = indexOnTileInTargetBoard % sizeBoard;
        int currentR = i / sizeBoard;
        int currentC = i % sizeBoard;
       manhattanDist += (abs(currentR - targetR) + abs(currentR - targetR));
    }
    return manhattanDist;
}

int BoardWithTiles::getManhattan(BoardWithTiles target)
{
    if(manhattanDist == -1)
    {
       manhattanDist = manhattan(target);
    }
    return manhattanDist;
}

int BoardWithTiles::findPos(int tile)
{
    return (std::find(tiles.begin(), tiles.end(), tile)) - tiles.begin();
}

void BoardWithTiles::print()
{
    size_t tileSize = tiles.size();
    for(int i = 0; i < tileSize; ++i)
    {
        std::cout << tiles[i] << ' ';
        if((i + 1) % sizeBoard == 0)
        {
            std::cout << std::endl;
        }
    }
}

bool operator==(const BoardWithTiles &board1, const BoardWithTiles &board2)
{
    return board1.tiles == board2.tiles;
}

bool operator<(const BoardWithTiles &board1, const BoardWithTiles &board2)
{
    return board1.manhattanDist > board2.manhattanDist;
}

std::priority_queue<BoardWithTiles> BoardWithTiles::getNeighbours()
{
    std::priority_queue<BoardWithTiles> neighbours;

    if(trail != 'u' && tileEmpty - sizeBoard >= 0)
    {
        std::swap(tiles[tileEmpty], tiles[tileEmpty-sizeBoard]);

        BoardWithTiles child(tiles);
        child.trail = 'd';
        neighbours.push(child);

        std::swap(tiles[tileEmpty], tiles[tileEmpty - sizeBoard]);
    }
    if(trail != 'd' && tileEmpty + sizeBoard < tiles.size())
    {
        std::swap(tiles[tileEmpty], tiles[tileEmpty + sizeBoard]);

        BoardWithTiles child(tiles);
        child.trail = 'u';
        neighbours.push(child);

        std::swap(tiles[tileEmpty], tiles[tileEmpty + sizeBoard]);
    }
    if(trail != 'l' && tileEmpty > 0 && tileEmpty / sizeBoard == (tileEmpty - 1) / sizeBoard)
    {
       std::swap(tiles[tileEmpty], tiles[tileEmpty - 1]);

       BoardWithTiles child(tiles);
       child.trail = 'r';
       neighbours.push(child);

       std::swap(tiles[tileEmpty], tiles[tileEmpty - 1]);
    }
    if(trail !='r' && tileEmpty / sizeBoard == (tileEmpty + 1) / sizeBoard)
    {
        std::swap(tiles[tileEmpty], tiles[tileEmpty + 1]);

        BoardWithTiles child(tiles);
        child.trail = 'l';
        neighbours.push(child);

        std::swap(tiles[tileEmpty], tiles[tileEmpty + 1]);
    }

    return neighbours;
}