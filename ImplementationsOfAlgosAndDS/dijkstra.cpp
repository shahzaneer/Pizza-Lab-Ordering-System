#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int infinity = INT_MAX;
const int maxVerticesInGraph = 100;

vector<pair<int, int>> graph[maxVerticesInGraph];

// the function will return the vector with minimum distances
vector<int> dijkstra(int sourceNode)
{
    vector<int> distance(maxVerticesInGraph, infinity);
    set<pair<int, int>> s;
    distance[sourceNode] = 0;
    // current weight of source node , sourceNode
    s.insert(make_pair(0, sourceNode));

    while (!s.empty())
    {
        auto top = *(s.begin());
        int u = top.first;  //   current weight
        int v = top.second; //  current vertex

        s.erase(s.begin());

        // traversing the adjacency list of v
        for (auto child : graph[v])
        {
            int childVertex = child.first;
            int childWeight = child.second;

            if (u + childWeight < distance[childVertex])
            {
                distance[childVertex] = u + childWeight;
                s.insert(make_pair(distance[childVertex], childVertex));
            }
        }
    }

    return distance;
}

int main()
{
    cout << "Enter the number of vertices" << endl;
    int vertices;
    cin >> vertices;

    cout << "Enter the number of edges" << endl;
    int edges;
    cin >> edges;

    // for edges

    for (int i = 0; i < edges; i++)
    {
        int first_vertex;
        cout << "Enter the first Vertex " << endl;
        cin >> first_vertex;

        int second_vertex;
        cout << "Enter the second Vertex " << endl;
        cin >> second_vertex;

        int weight;
        cout << "Enter the weight of this edge " << endl;
        cin >> weight;

        // making of the graph
        // directed graph
        graph[first_vertex].push_back(make_pair(second_vertex, weight));
    }

    vector<int> distance = dijkstra(1);

    for (int i = 0; i < vertices; i++)
    {
        cout << "Distance between "
             << "0"
             << " and " << i << " is " << distance[i] << endl;
    }

    return 0;
}