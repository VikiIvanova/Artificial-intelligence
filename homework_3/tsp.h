#ifndef TSP_H
#define TSP_H

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <time.h>
#include <stdlib.h>

class Graph
{
private:
    int n;
    int totalEdges;
    int initialVertex;
    std::map<std::pair<int, int>, int> mapEdges;

public:
    Graph(int n, int initialVertex, bool randomGraph = false);
    void addEdge(int v1, int v2, int weight);
    void printGraph();
    void generateGraph();
    void printInfoGraph();
    int existsEdge(int src, int dest);
    friend class Genetic;
};

typedef std::pair<std::vector<int>, int> myPair;

struct sortPair
{
    bool operator()(const myPair &firstElement, const myPair &secondElement)
    {
        return firstElement.second < secondElement.second;
    }
};

class Genetic
{
private:
    Graph *graph;
    std::vector<myPair> population;
    int sizePopulation;
    int realSizePopulation;
    int generations;
    int mutationRate;
    bool showPopulation;

    void initialPopulation();

public:
    Genetic(Graph *graph, int amountPopulation, int generations, int mutationRate, bool showPopulation = true);
    int isValidSolution(std::vector<int> &solution);
    void printPopulation();
    void crossOver(std::vector<int> &parent1, std::vector<int> &parent2);
    void insertBinarySearch(std::vector<int> &child, int totalCost);
    void run();
    int getCostBestSolution();
    bool existsChromosome(const std::vector<int> &v);
};

#endif
