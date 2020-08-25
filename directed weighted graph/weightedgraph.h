#pragma once
#ifndef GRAPH_CLASS
#include <iostream>
#define GRAPH_CLASS
#define V 5
#define UNVISITED 0
#define VISITED 1
using namespace std;
class Graph
{
private:
    int numVertex, numEdge;
    int** matrix;//The adjacency matrix
    int* mark;//array of visited nodes
   
public:
    // Constructor 
    Graph(int n) {
        int i;
        numVertex = n;
        numEdge = 0;
        mark = new int[numVertex];	// Initialize mark array with dynamic memory allocation
        for (i = 0; i < numVertex; i++) {
            mark[i] = UNVISITED;
         
        }
        // Make matrix, it is not possible to create 2D array with a single new operation. Size is numVertex* numVertex
        matrix = new int* [numVertex];
        for (i = 0; i < numVertex; i++)
            matrix[i] = new int[numVertex];
        for (i = 0; i < numVertex; i++) // Initialize to 0 all elements of adjacency matrix
            for (int j = 0; j < numVertex; j++)
                matrix[i][j] = 0;
    };
    ~Graph() { // Destructor, Return dynamically allocated memory
        delete[] mark;
        for (int i = 0; i < numVertex; i++)
            delete[] matrix[i];
        delete[] matrix;
    };
   
    // Return first neighbor of vertex v 
    int first(int v) {
        for (int i = 0; i < numVertex; i++)
            if (matrix[v][i] != 0)
                return i;
        return numVertex;	// Return n if none
    };
    // Return v’s next neighbor after w
    int next(int v, int w) {
        for (int i = w + 1; i < numVertex; i++)
            if (matrix[v][i] != 0)
                return i;
        return numVertex; // Return n if none
    };    
    // Set edge (v1, v2) with weight wt
    void setEdge(int v1, int v2, int wt) {
        if (matrix[v1][v2] == 0)
            numEdge++; matrix[v1][v2] = wt;
    };
    void delEdge(int v1, int v2) { // Delete edge (v1, v2)
        if (matrix[v1][v2] != 0)
            numEdge--;
        matrix[v1][v2] = 0;
    };
    //clear the mark array as UNVISITED
    void clearMark(void) {
        for (int i = 0; i < numVertex; i++)
            mark[i] = UNVISITED;
    }
    //Min distance is an auxiliary function for dijkstra algorithm 
    int minDistance(int dist[], bool sptSet[])
    {
        // Initialize min value
        int min_val = INT_MAX, min_index;

        for (int v = 0; v < V; v++)
            if (sptSet[v] == false && dist[v] <= min_val) {
                min_val = dist[v];
                min_index = v;
            }

        return min_index;
    }

    // A utility function to print the constructed distance array
    void printSolution(int dist[], int n, int prev[])
    {
        printf("Vertex   Distance from Source\n");
        for (int i = 0; i < V; i++) {
            cout << "the node: " << i << " previous node: " << prev[i] << " cost: " << dist[i] << endl;

        }
    }
  
    /* Function that implements Dijkstra's single source shortest path algorithm
     for a graph represented using adjacency matrix representation
     which gives the shortest path between two nodes .
     Note that first input is source node and second input is target node  */
    int dijkstra(int src,int target)
    {
        int dist[V]; // The output array.  dist[i] will hold the shortest distance from src to i
        int prev[V];
        bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from source to i is finalized

        // Initialize all distances as INFINITE and stpSet[] as false
        for (int i = 0; i < V; i++)
            dist[i] = INT_MAX, sptSet[i] = false, prev[i] = -1;

        // Distance of source vertex from itself is always 0
        dist[src] = 0;

        // Find shortest path for all vertices
        for (int count = 0; count < V - 1; count++) {
            // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
            int u = minDistance(dist, sptSet);

            // Mark the picked vertex as processed
            sptSet[u] = true;
            if (dist[u] == INT_MAX)
                break;
            // Update dist value of the adjacent vertices of the picked vertex.
            for (int v = 0; v < V; v++)
                if (matrix[u][v]) {//the vertices exist
                    if (!sptSet[v]) {
                        int cand = dist[u] + matrix[u][v];
                        if (cand < dist[v]) {//if candidate is smaller than dist[u] ,new dist[u] is candidate 
                            dist[v] = cand;
                            prev[v] = u;
                        }


                    }
                }
        }
       
        // print the constructed distance array from given source vertex
        printSolution(dist, V, prev);
        return dist[target];
    }
    //findingcycle is a utility recursive function to detect the graph is acyclic or not. 
    bool findingcycle(int v, bool visited[], bool* recStack)
    {
        if (visited[v] == false)
        {
            // Mark the current node as visited and part of recursion stack
            visited[v] = true;
            recStack[v] = true;

            // Recur for all the vertices adjacent to this vertex

            for (int i = first(v); i != numVertex; i = next(v, i))
            {
                if (!visited[i] && findingcycle(i, visited, recStack))
                    return true;
                else if (recStack[i])
                    return true;
            }

        }
        recStack[v] = false;  // remove the vertex from recursion stack
        return false;
    }
    //isCyclic function determines the given graph is cyclic or nor.
    bool isCyclic()
    {
        // Mark all the vertices as not visited and not part of recursion stack
        bool* visited = new bool[V];
        bool* recStack = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
            recStack[i] = false;
        }

        // Call the recursive helper function to detect cycle in different depth first search graphs
        for (int i = 0; i < V; i++)
            if (findingcycle(i, visited, recStack))
                return true;

        return false;
    }
};
#endif