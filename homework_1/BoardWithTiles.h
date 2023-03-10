#ifndef BOARDWITHTILES_H
#define BOARDWITHTILES_H

#include <vector>
#include <queue>
class BoardWithTiles
{
    private:
    std::vector<int> tiles;
    int sizeBoard;
    int tileEmpty;
    int manhattanDist;
    char trail; 

    int findPos(int tile);
    int manhattan(BoardWithTiles target);

    public:
    BoardWithTiles();
    BoardWithTiles(std::vector<int> tiles);
    int getTileEmpty();
    char getTrail();
    int getManhattan(BoardWithTiles target);
    std::priority_queue<BoardWithTiles> getNeighbours();
    void print();

    friend bool operator==(const BoardWithTiles &board1, const BoardWithTiles &board2);
    friend bool operator<(const BoardWithTiles &board1, const BoardWithTiles &board2);

};

#endif