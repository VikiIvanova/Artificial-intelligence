#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <algorithm>

const long MAXITERATION = 100000000;

void move(int row, int newCol, std::vector<int> &board,
          std::vector<std::vector<int>> &confMatrix)
{
    int prevCol = board[row];
    board[row] = newCol;
    for (int i = 0; i < board.size(); ++i)
    {
        if (i == row)
        {
            continue;
        }
        confMatrix[i][prevCol]--;
        if (prevCol + row - i >= 0 && prevCol + row - i < board.size())
        {
            confMatrix[i][prevCol + row - i]--;
        }
        if (prevCol - row + i >= 0 && prevCol - row + i < board.size())
        {
            confMatrix[i][prevCol - row + i]--;
        }
        confMatrix[i][newCol]++;
        if (newCol + row - i >= 0 && newCol + row - i < board.size())
        {
            confMatrix[i][newCol + row - i]++;
        }
        if (newCol - row + i >= 0 && newCol - row + i < board.size())
        {
            confMatrix[i][newCol - row + i]++;
        }
    }
}

void Init(int n, std::vector<int> &board, std::vector<std::vector<int>> &confMatrix)
{
    board.clear();
    board.reserve(n);
    static std::mt19937 rand(time(0));
    static std::uniform_int_distribution<int> generator(0, n - 1);
    for (int i = 0; i < n; ++i)
    {
        board.push_back(i);
    }
    for (int i = 0; i < n; ++i)
    {
        std::swap(board[i], board[generator(rand)]);
    }
    confMatrix = move(std::vector<std::vector<int>>(n, std::vector<int>(n, 0)));
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board.size(); ++j)
        {
            if (i == j)
            {
                continue;
            }
            confMatrix[j][board[i]]++;
            if (board[i] + j - i >= 0 && board[i] + j - i < board.size())
            {
                confMatrix[j][board[i] + j - i]++;
            }
            if (board[i] - j + i >= 0 && board[i] - j + i < board.size())
            {
                confMatrix[j][board[i] - j + i]++;
            }
        }
    }
}

void NQueens(const int n, std::vector<int> &board)
{
    std::vector<std::vector<int>> confMatrix;
    Init(n, board, confMatrix);

    static std::mt19937 rand(time(0));
    std::uniform_int_distribution<int> generator(0, n - 1);

    int maxConfCount;
    std::vector<int> maxConfVec;
    maxConfVec.reserve(n);

    int minConfCount;
    std::vector<int> minConfVec;
    minConfVec.reserve(n);

    int counter = 0;
    while (counter < MAXITERATION)
    {
        counter++;
        maxConfCount = 0;
        maxConfVec.clear();
        for (int i = 0; i < board.size(); ++i)
        {
            if (maxConfCount == confMatrix[i][board[i]])
            {
                maxConfVec.push_back(i);
            }
            else if (confMatrix[i][board[i]] > maxConfCount)
            {
                maxConfVec.clear();
                maxConfVec.push_back(i);
                maxConfCount = confMatrix[i][board[i]];
            }
        }
        if (maxConfCount == 0)
        {
            break;
        }
        generator.param(std::uniform_int_distribution<int>::param_type(0, maxConfVec.size() - 1));
        int worstQueen = maxConfVec[generator(rand)];

        minConfVec.clear();
        minConfCount = n;
        for (int col = 0; col < n; ++col)
        {
            int currConfCount = confMatrix[worstQueen][col];
            if (currConfCount == minConfCount)
            {
                minConfVec.push_back(col);
            }
            else if (currConfCount < minConfCount)
            {
                minConfCount = currConfCount;
                minConfVec.clear();
                minConfVec.push_back(col);
            }
        }
        if(!minConfVec.empty())
        {
            generator.param(std::uniform_int_distribution<int>::param_type(0, minConfVec.size() - 1));
            move(worstQueen, minConfVec[generator(rand)], board, confMatrix);
        }
        if (counter % (2 * n) == 0)
        {
            Init(n, board, confMatrix);
        }
    }
    int totalConf = 0;
    for (int i = 0; i < n; ++i)
    {
        totalConf += confMatrix[i][board[i]];
    }
}

void print(std::vector<int> &board)
{
    for_each(board.begin(), board.end(), [&board](int pos)
             {
        for(int i = 0; i < board.size(); ++i)
        {
            if(i == pos)
            {
                std::cout << "*";
            }
            else
            {
                std::cout << "_";
            }
        }
         std::cout << std::endl; });
}

int main()
{
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;
    std::vector<int> board(n);
    long startTime = time(0);
    NQueens(n, board);
    std::cout << "Еxecution time: " << (time(0) - startTime) << " seconds" << std::endl;

    if (n < 500)
    {
        print(board);
    }

    return 0;
}