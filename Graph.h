#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#define V 1000
using namespace std;

// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list
    vector<vector<int>> adjList;
    const int v;
    int u;

    // Graph Constructor
    Graph(int N):v(N)
    {
        // resize the vector to hold `N` elements of type `vector<int>`
        adjList.resize(N);
        u = 0;
    }
    void addEdge(int start, int end);
    int vertexDegree(int vertex);
};
Graph build_random_graph(int N, float p);

void printGraph(Graph const& graph);

bool visited(Graph graph, int n1, int n2);
bool Is_Isolated(Graph graph);
bool connectivity(Graph graph);
int diameter(Graph graph);
int bfs(Graph g, int v);
int bfs_diam(Graph graph, int v);
int diameter2(Graph g);
