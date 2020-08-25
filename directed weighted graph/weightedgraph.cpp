#include <iostream>
#include "weightedgraph.h"
//#include "gtest/gtest.h"
#define V 5
#define UNVISITED 0
#define VISITED 1
using namespace std;


int main() {
    Graph G(V);
    G.clearMark();
    G.setEdge(0, 1, 3);
    G.setEdge(0, 3, 7);
    G.setEdge(0, 4, 8);
    G.setEdge(1, 2, 1);
    G.setEdge(1, 3, 4);
    G.setEdge(3, 2, 2);
    G.setEdge(4, 3, 3);
    cout << endl;
    G.dijkstra(0, 1);
    if (G.isCyclic())
        cout << "The graph is cyclic" << endl;
    else
        cout << "The graph is acyclic" << endl;
    return 0;
}
