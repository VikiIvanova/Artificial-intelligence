#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void print(const std::string &board)
{
    for (int i = 0; i < 9; ++i)
    {
        if (i % 3 == 0 && i != 0)
        {
            std::cout << std::endl;
        }
        std::cout << board[i] << "|";
    }
}

char winner(const std::string &board)
{
    if ((board[0] == board[1] && board[1] == board[2] && board[0] == 'X') ||
        (board[3] == board[4] && board[4] == board[5] && board[3] == 'X') ||
        (board[6] == board[7] && board[7] == board[8] && board[6] == 'X') ||
        (board[0] == board[3] && board[3] == board[6] && board[0] == 'X') ||
        (board[1] == board[4] && board[4] == board[7] && board[1] == 'X') ||
        (board[2] == board[5] && board[5] == board[8] && board[2] == 'X') ||
        (board[0] == board[4] && board[4] == board[8] && board[0] == 'X') ||
        (board[2] == board[4] && board[4] == board[6] && board[2] == 'X'))
    {
        return 'X';
    }
    else if ((board[0] == board[1] && board[1] == board[2] && board[0] == 'O') ||
             (board[3] == board[4] && board[4] == board[5] && board[3] == 'O') ||
             (board[6] == board[7] && board[7] == board[8] && board[6] == 'O') ||
             (board[0] == board[3] && board[3] == board[6] && board[0] == 'O') ||
             (board[1] == board[4] && board[4] == board[7] && board[1] == 'O') ||
             (board[2] == board[5] && board[5] == board[8] && board[2] == 'O') ||
             (board[0] == board[4] && board[4] == board[8] && board[0] == 'O') ||
             (board[2] == board[4] && board[4] == board[6] && board[2] == 'O'))
    {
        return 'O';
    }
    else
    {
        return 'D';
    }
}

bool move(int pos, char player, std::string &board)
{
    if (board[pos] == ' ')
    {
        board[pos] = player;
        return true;
    }
    return false;
}

int alphaBeta(std::string board, char player, int depth, int alpha, int beta, bool maximizingPlayer)
{
    char next;
    player == 'X' ? next = 'O' : next = 'X';

    char maxPlayer;
    maximizingPlayer == false ? maxPlayer = player : maxPlayer = next;
    if (winner(board) == maxPlayer)
    {
        return -10;
    }
    else if (winner(board) != 'D')
    {
        return 10;
    }
    else if (winner(board) == 'D' && depth == 9)
    {
        return 0;
    }
    if (maximizingPlayer)
    {
        int v = -100;
        for (int i = 0; i < 9; i++)
        {
            std::string childBoard = board;
            if (move(i, player, childBoard))
            {
                v = std::max(v, alphaBeta(childBoard, next, depth + 1, alpha, beta, false));
                alpha = std::max(alpha, v);
                if (alpha >= beta)
                    break;
            }
        }
        return v;
    }
    else
    {
        int v = 100;
        for (int i = 0; i < 9; i++)
        {
            std::string childBoard = board;
            if (move(i, player, childBoard))
            {
                v = std::min(v, alphaBeta(childBoard, next, depth + 1, alpha, beta, true));
                beta = std::min(beta, v);
                if (alpha >= beta)
                    break;
            }
        }
        return v;
    }
}

void AIMove(int turn, char player, std::string &board)
{
    std::pair<int, std::string> optimalMove = {-100, ""};
    char next;
    player == 'X' ? next = 'O' : next = 'X';

    std::vector<int> index;
    if (index.empty())
    {
        for (int i = 0; i < 9; i++)
        {
            index.push_back(i);
        }
        random_shuffle(index.begin(), index.end());
        for (int i = 0; i < 9; i++)
        {
            std::string childBoard = board;
            if (move(index[i], player, childBoard))
            {
                int v = alphaBeta(childBoard, next, turn + 1, -100, 100, false);
                if (v > optimalMove.first)
                {
                    optimalMove.first = v;
                    optimalMove.second = childBoard;
                }
                if (v == 10)
                    break;
            }
        }
        board = optimalMove.second;
    }
}

char game(bool AIfirst)
{
    std::string board(9, ' ');
    fill(board.begin(), board.end(), ' ');
    int turn = 0, x, y;
    while (winner(board) == 'D' && turn < 9)
    {
        if ((turn + AIfirst) % 2 == 0)
        {
            do
            {
                std::cin >> x >> y;
            } while (!move(y - 1 + (x - 1) * 3, 'X', board));
        }
        else
        {
            AIMove(turn, 'O', board);
        }
        print(board);
        std::cout << std::endl
                  << std::endl;
        turn++;
    }
    return winner(board);
}

int main()
{
    int first = 1;
    char ans;
    do 
    {
        char winner = game(first % 2 == 0);
        if(winner != 'D')
        {
            std::cout << "Winner: " << winner << std::endl;
        }
        else
        {
           std::cout << "Draw! " << std::endl;
        }
        first++;
        std::cout << "New game? (y/n): ";
        std::cin >> ans;
    }while(ans == 'y');

    return 0;
}