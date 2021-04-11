#include "Graph.h"
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

Graph build_random_graph(int N,float p)
{
    Graph g(N);
    
    // add edges to the graph
    for (int i = 0;i < N-1;i++)
    {
        for (int j = i+1; j < N; j++)
        {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if (r <= p)
            {
                g.u++;
                g.addEdge(i, j);
            }

        }

    }
    return g;
}

bool Is_Isolated(Graph g)
{
    for (int i = 0; i < g.v; i++)
    {
        if (g.vertexDegree(i)== 0)
            return true;
    }
    return false;
}

bool connectivity(Graph g)
{
    int temp = bfs(g, 0);
    return temp==INT_MAX?0:1;
}

int diameter(Graph g)
{
    int diam = bfs(g, 0);
    int temp;
    if (diam == INT_MAX)
        return diam;
    for (int i = 1; i < g.v; i++)
    {

        temp = bfs(g, i);
        if (temp > diam)
            diam = temp;

    }
    return diam;
}

// Additional auxiliary functions

void printGraph(Graph const& graph)
{
    cout << "connection between nodes" << endl;
    for (int i = 0; i < graph.v; i++)
    {

        cout << i << ":";
        // print all neighboring vertices of a vertex `i`
        for (int v : graph.adjList[i]) {
            cout << "{" << i << ", " << v << "},";
        }
        cout << endl;
    }
}

int bfs(Graph graph,int v)
{
    // Initializing queue
    queue<int> q;
    int diam = 0;
    int Vertexs = 1;
    int* visited = new int[graph.v+1]();
    int* Diameter = new int[graph.v+1]();
    // Pushing each node in queue
    q.push(v);
    // Mark the traversed node visited
    visited[v] = 1;
    Diameter[v] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < graph.adjList[u].size(); i++) {
            if (visited[graph.adjList[u][i]] == 0) {
                visited[graph.adjList[u][i]] = 1;
                // Considering weight of edges equal to 1
                Diameter[graph.adjList[u][i]] = Diameter[u] + 1;
                diam = diam > Diameter[graph.adjList[u][i]] ? diam : Diameter[graph.adjList[u][i]];
                q.push(graph.adjList[u][i]);
                Vertexs++;
            }
        }
    }

    // return max value in diameter
    //diam = Diameter[int(max_element(Diameter + 1,Diameter + graph.v + 1)- Diameter)];//todo
    return Vertexs== graph.v?diam:INT_MAX;
}

void Graph::addEdge(int start, int end) {
    adjList[start].push_back(end);
    adjList[end].push_back(start);
}

int Graph::vertexDegree(int vertex) {
    return adjList[vertex].size();
}
