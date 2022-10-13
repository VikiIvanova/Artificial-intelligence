/*
Advantages of Depth Limited Search
1.Depth limited search is more efficient than DFS, using less time and memory.
2.If a solution exists, DFS guarantees that it will be found in a finite amount of time.
3.To address the drawbacks of DFS, we set a depth limit and run our search technique repeatedly through the search tree.
4.DLS has applications in graph theory that are highly comparable to DFS.

Disadvantages of Depth Limited Search
1.For this method to work, it must have a depth limit.
2.If the target node does not exist inside the chosen depth limit, the user will be forced to iterate again, increasing execution time.
3.If the goal node does not exist within the specified limit, it will not be discovered.

IDDFS combines depth-first search’s space-efficiency and breadth-first search’s fast search (for nodes closer to root). 

How does IDDFS work? 
IDDFS calls DFS for different depths starting from an initial value. In every call, DFS is restricted from going beyond given depth. */


#include <iostream>
#include <list>

class Graph
{
    int nVertices;
    std::list<int> *adjLists;
    bool *visited;

public:
    Graph(int vertices);
    void addEdge(int src, int dest);
    void showGraph(Graph g, int vertices);
    bool IDDFS(int src, int dest, int maxDepth);
    bool DLS(int src, int dest, int limit);
   
};
Graph::Graph(int vertices)
{
    nVertices = vertices;
    adjLists = new std::list<int>[vertices];
}
void Graph::addEdge(int src, int dest)
{
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src);
}

void Graph::showGraph(Graph g, int vertices)
{
    for(int i = 0; i < vertices; ++i)
    {
        std::cout << i << " -> ";
        for(int v : g.adjLists[i])
        {
            std::cout << v << " ";
        }
         std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Graph::DLS(int src, int dest, int limit)
{
    if(src == dest)
       return true;
    if(limit <= 0)
       return false;
    for(auto i = adjLists[src].begin(); i != adjLists[src].end(); ++i)
       if(DLS(*i, dest, limit-1) == true)
          return true;

    return false;
}

bool Graph::IDDFS(int src, int dest, int maxDepth)
{
    for(int i = 0; i <= maxDepth; ++i)
        if(DLS(src, dest, i) == true)
             return true;

    return false;

}

int main()
{
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
   
   int dest = 6, maxDepth = 3, src = 0;
   std::cout << std::boolalpha <<g.DLS(src, dest, maxDepth) << std::endl;
   std::cout << std::boolalpha << g.IDDFS(src, dest, maxDepth) << std::endl;

   return 0;
}

