#include <iostream>
using namespace std;

// DFS Traversal
// DFS is Depth first search traversal
// In DFS we maintain two things one is the visited array and other is inbuilt stack of the compiler! (Recursion)
// The stack will store the vertices which are not visited yet
// The visited array will store the vertices which are visited
// When the Vertex is visited and all other vertices related to it are also pushed then we will pop the vertex
//! DFS Traversal is also Never unique!!
//! Even after Starting from the same node we may not get the same result

// *Globally declaring the Graph
int i = 1;                              // starting Node for traversal
int visited[7] = {0, 0, 0, 0, 0, 0, 0}; // visited array
int adjacencyMatrix[7][7] =
    {{0, 1, 1, 1, 0, 0, 0},
     {1, 0, 0, 1, 0, 0, 0},
     {1, 0, 0, 1, 1, 0, 0},
     {0, 1, 1, 0, 1, 0, 0},
     {0, 0, 1, 1, 0, 1, 1},
     {0, 0, 0, 0, 1, 0, 0},
     {0, 0, 0, 0, 1, 0, 0}}; // See a graph and place 1 where there is an edge

void DFS(int startingNode)
{
    cout << startingNode << " ";
    visited[startingNode] = 1;
    for (int i = 0; i < 7; i++)
    {
        if (adjacencyMatrix[startingNode][i] == 1 && visited[i] == 0)
        {
            DFS(i);
        }
    }
    // return; // writing this is not necessary as we know there are two ways for the returning of a function .
    // one is return; second is end of function as there end of function is approaching so it is redundant to write return;
}

int main()
{

    DFS(i);
    return 0;
}