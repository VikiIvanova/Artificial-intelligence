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
    void BFS(int startVertex);
    void DFS(int startVertex);
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
void Graph::BFS(int startVertex)
{
    visited = new bool[nVertices];
    for (int i = 0; i < nVertices; i++)
    {
        visited[i] = false;
    }

    std::list<int> queue;

    visited[startVertex] = true;
    queue.push_back(startVertex);

    std::list<int>::iterator i;

    while (!queue.empty())
    {
        int currVertex = queue.front();
        std::cout << "Visited " << currVertex << " " << std::endl;
        queue.pop_front();

        for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i)
        {
            int adjVertex = *i;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }
}
void Graph::DFS(int vertex)
{
    visited[vertex] = true;
    std::list<int> adjList = adjLists[vertex];

    std::cout << vertex << " ";

    std::list<int>::iterator i;
    for (i = adjList.begin(); i != adjList.end(); ++i)
    {
        if (!visited[*i])
            DFS(*i);
    }
}

int main()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    std::cout << "graphVertex: " << std::endl;
    g.showGraph(g, 4);
    
    std::cout << "BFS:" << std::endl;
    g.BFS(2);
    std::cout << "DFS:" << std::endl;
    g.DFS(2);
    std::cout << std::endl; 
    g.DFS(3);
    std::cout << std::endl;

    return 0;
}
