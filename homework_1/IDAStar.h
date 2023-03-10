#ifndef IDASTAR_H
#define IDASTAR_H

#include "BoardWithTiles.h"

#include <queue>
#include <stack>

class IDAStar
{
    private:
    BoardWithTiles start;
    BoardWithTiles target;
    int bound;
    std::stack<BoardWithTiles> targetPath;

    int search(int countLevels, std::stack<BoardWithTiles>& paths);

    public:
    IDAStar(BoardWithTiles start, BoardWithTiles target);
    void findPath();
    void printPath();
};

#endif