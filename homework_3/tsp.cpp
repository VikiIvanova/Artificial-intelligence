#include <iostream>
#include <algorithm>
#include "tsp.h"

Graph::Graph(int n, int initialVertex, bool randomGraph)
{
    this->n = n;
    this->initialVertex = initialVertex;
    this->totalEdges = 0;

    if (randomGraph)
    {
        generateGraph();
    }
}

void Graph::generateGraph()
{
    std::vector<int> graph;

    for (int i = 0; i < n; ++i)
    {
        graph.push_back(i);
    }

    std::random_shuffle(graph.begin(), graph.end());

    initialVertex = graph[0];
    int weight = 0;
    for (int i = 0; i <= n; ++i)
    {
        weight = rand() % n + 1;
        if (i + 1 < n)
        {
            addEdge(graph[i], graph[i + 1], weight);
        }
        else
        {

            addEdge(graph[i], graph[0], weight);
            break;
        }
    }
    int limitEdges = n * (n - 1);
    int sizeEdges = rand() % (2 * limitEdges) + limitEdges;

    for (int i = 0; i < sizeEdges; ++i)
    {
        int src = rand() % n;
        int dest = rand() % n;
        weight = rand() % n + 1;
        if (src != dest)
        {
            addEdge(graph[src], graph[dest], weight);
            addEdge(graph[dest], graph[src], weight);
        }
    }
}

void Graph::printInfoGraph()
{
    std::cout << "Showing info of graph:" << std::endl;
    std::cout << "Number of vertices: " << n << std::endl;
    std::cout << "Number of edges: " << mapEdges.size() << std::endl;
}

void Graph::addEdge(int src, int dest, int weight)
{
    mapEdges[std::make_pair(src, dest)] = weight;
}

int Graph::existsEdge(int src, int dest)
{
    std::map<std::pair<int, int>, int>::iterator it = mapEdges.find(std::make_pair(src, dest));
    if (it != mapEdges.end())
    {
        return it->second;
    }
    return -1;
}

Genetic::Genetic(Graph *graph, int sizePopulation, int generations, int mutationRate, bool showPopulation)
{
    this->graph = graph;
    this->sizePopulation = sizePopulation;
    this->realSizePopulation = 0;
    this->generations = generations;
    this->mutationRate = mutationRate;
    this->showPopulation = showPopulation;
}

int Genetic::isValidSolution(std::vector<int> &solution)
{
    int totalCost = 0;
    std::set<int> setSolution;

    for (int i = 0; i < graph->n; ++i)
    {
        setSolution.insert(solution[i]);
    }
    if (setSolution.size() != (unsigned)graph->n)
    {
        return -1;
    }

    for (int i = 0; i < graph->n; ++i)
    {
        if (i + 1 < graph->n)
        {
            int cost = graph->existsEdge(solution[i], solution[i + 1]);
            if (cost == -1)
            {
                return -1;
            }
            else
            {
                totalCost += cost;
            }
        }
        else
        {
            int cost = graph->existsEdge(solution[i], solution[0]);

            if (cost == -1)
            {
                return -1;
            }
            else
            {
                totalCost += cost;
            }
            break;
        }
    }
    return totalCost;
}

bool Genetic::existsChromosome(const std::vector<int> &v)
{

    for (std::vector<std::pair<std::vector<int>, int>>::iterator it = population.begin(); it != population.end(); ++it)
    {
        const std::vector<int> &vec = (*it).first;
        if (equal(v.begin(), v.end(), v.begin()))
            return true;
    }
    return false;
}

void Genetic::initialPopulation()
{
    std::vector<int> parent;

    for (int i = 0; i < graph->n; ++i)
    {
        if (i != graph->initialVertex)
        {
            parent.push_back(i);
        }
    }
    int totalCost = isValidSolution(parent);
    if (totalCost != -1)
    {
        population.push_back(std::make_pair(parent, totalCost));
        realSizePopulation++;
    }

    for (int i = 0; i < generations; ++i)
    {

        std::random_shuffle(parent.begin() + 1, parent.begin() + rand() % (graph->n - 1) + 1);

        int totalCaost = isValidSolution(parent);

        if (totalCost != -1 && !existsChromosome(parent))
        {
            population.push_back(make_pair(parent, totalCost));
            realSizePopulation++;
        }
        if (realSizePopulation == sizePopulation)
        {
            break;
        }

        if (realSizePopulation == 0)
        {
        }
        else
        {
            std::sort(population.begin(), population.end());
        }
    }
}

void Genetic::printPopulation()
{
    std::cout << "\nShowing solution...\n\n";
    for (std::vector<std::pair<std::vector<int>, int>>::iterator it = population.begin(); it != population.end(); ++it)
    {
        const std::vector<int> &vec = (*it).first;
        for (int i = 0; i < graph->n; ++i)
        {
            std::cout << vec[i] << " ";
        }
        std::cout << graph->initialVertex;
        std::cout << " | Cost: " << (*it).second << "\n\n";
    }
    std::cout << "\nPopulation size: " << realSizePopulation << std::endl;
}

void Genetic::insertBinarySearch(std::vector<int> &child, int totalCost)
{
    int imin = 0;
    int imax = realSizePopulation - 1;

    while (imax >= imin)
    {
        int imid = imin + (imax - imin) / 2;
        if (totalCost == population[imid].second)
        {
            population.insert(population.begin() + imid, make_pair(child, totalCost));
        }
    }
}

void Genetic::crossOver(std::vector<int> &parent1, std::vector<int> &parent2)
{
    std::vector<int> child1, child2;

    std::map<int, int> genes1, genes2;
    for (int i = 0; i < graph->n; ++i)
    {

        genes1[parent1[i]] = 0;
        genes2[parent2[i]] = 0;
    }

    int point1 = rand() % (graph->n - 1) + 1;
    int point2 = rand() % (graph->n - point1) + point1;

    if (point1 == point2)
    {
        if (point1 - 1 > 1)
        {
            point1--;
        }
        else if (point2 + 1 < graph->n)
        {
            point2++;
        }
        else
        {
            int point = rand() % 10 + 1;
            if (point <= 5)
            {
                point1--;
            }
            else
            {
                point2++;
            }
        }
    }

    for (int i = 0; i < point1; ++i)
    {
        child1.push_back(parent1[i]);
        child2.push_back(parent2[i]);
        genes1[parent1[i]] = 1;
        genes2[parent2[i]] = 1;
    }

    for (int i = point2 + 1; i < graph->n; ++i)
    {
        genes1[parent1[i]] = 1;
        genes2[parent2[i]] = 1;
    }

    for (int i = point2; i >= point1; --i)
    {
        if (genes1[parent2[i]] == 0)
        {
            child1.push_back(parent2[i]);
            genes1[parent2[i]] = 1;
        }
        else
        {
            for (std::map<int, int>::iterator it = genes1.begin(); it != genes1.end(); ++it)
            {
                if (it->second == 0)
                {
                    child1.push_back(it->first);
                    genes1[it->first] = 1;
                    break;
                }
            }
        }
        if (genes2[parent1[i]] == 0)
        {
            child2.push_back(parent1[i]);
            genes2[parent1[i]] = 1;
        }
        else
        {

            for (std::map<int, int>::iterator it = genes2.begin(); it != genes2.end(); ++it)
            {
                if (it->second == 0)
                {
                    child2.push_back(it->first);
                    genes2[it->first] = 1;
                    break;
                }
            }
        }
    }

    for (int i = point2 + 1; i < graph->n; ++i)
    {
        child1.push_back(parent1[i]);
        child2.push_back(parent2[i]);
    }

    int mutation = rand() % 100 + 1;
    if (mutation <= mutationRate)

        int indexGene1, indexGene2;
    indexGene1 = rand() % (graph->n - 1) + 1;
    indexGene2 = rand() % (graph->n - 1) + 1;
    int aux = child1[indexGene1];
    child1[indexGene1] = child1[indexGene2];
    child1[indexGene2] = aux;

    aux = child2[indexGene1];
    child2[indexGene1] = child2[indexGene2];
    child2[indexGene2] = aux;
}
int totalCostChild1 = isValidSolution(child1);
int totalCostChild2 = isValidSolution(child2);

if (totalCostChild1 != -1 && !existsChromosome(child1))
{

    insertBinarySearch(child1, totalCostChild1);
    realSizePopulation++;
}

if (totalCostChild2 != -1 && !existsChromosome(child2))
{

    insertBinarySearch(child2, totalCostChild2);
    realSizePopulation++;
}
}

void Genetic::run()
{
    initialPopulation();
    if (realSizePopulation == 0)
    {
        return;
    }
    for (int i = 0; i < generations; ++i)
    {
        int oldSizePopulation = realSizePopulation;

        if (realSizePopulation >= 2)
        {
            if (realSizePopulation == 2)
            {
                crossOver(population[0].first, population[1].first);
            }
            else
            {
                int parent1, parent2;
                do
                {
                    parent1 = rand() % realSizePopulation;
                    parent2 = rand() % realSizePopulation;
                } while (parent1 == parent2);

                crossOver(population[parent1].first, population[parent2].first);
            }

            int diffPopulation = realSizePopulation - oldSizePopulation;

            if (diffPopulation == 2)
            {
                if (realSizePopulation > sizePopulation)
                {

                    population.pop_back();
                    population.pop_back();

                    realSizePopulation -= 2;
                }
            }
            else if (diffPopulation == 1)
            {
                if (realSizePopulation > sizePopulation)
                {
                    population.pop_back();
                    realSizePopulation--;
                }
            }
        }

        else
        {

            crossOver(population[0].first, population[0].first);

            if (realSizePopulation > sizePopulation)
            {
                population.pop_back();
                realSizePopulation--;
            }
        }
    }
    if (showPopulation == true)
    {
        printPopulation();
    }
    std::cout << "\n Best solution: ";
    const std::vector<int> &vec = population[0].first;
    for (int i = 0; i < graph->n; ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << graph->initialVertex;
    std::cout << " | Cost: " << population[0].second;
}

int Genetic::getCostBestSolution()
{
    if (realSizePopulation > 0)
    {
        return population[0].second;
    }
    return -1;
}