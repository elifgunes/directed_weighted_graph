#include "pch.h"
#include "../directed weighted graph/weightedgraph.h"
#include "gtest/gtest.h"
TEST(Graph_acyclic_Test, cyclic) {
    Graph G(5);
    G.clearMark();
    G.setEdge(0, 1, 3);
    G.setEdge(0, 3, 7);
    G.setEdge(0, 4, 8);
    G.setEdge(1, 2, 1);
    G.setEdge(1, 3, 4);
    G.setEdge(3, 0, 5);//to make the graph cyclic ,this edge is added to the graph.
    G.setEdge(3, 2, 2);
    G.setEdge(4, 3, 3);

  EXPECT_EQ(1, G.isCyclic());//

}
TEST(Graph_acyclic_Test, acyclic) {
    Graph G(5);
    G.clearMark();
    G.setEdge(0, 1, 3);
    G.setEdge(0, 3, 7);
    G.setEdge(0, 4, 8);
    G.setEdge(1, 2, 1);
    G.setEdge(1, 3, 4);
    G.setEdge(3, 2, 2);
    G.setEdge(4, 3, 3);

    EXPECT_EQ(0, G.isCyclic());

}
TEST(Shortestpath_Test_Dijkstra, given_graph) {
    Graph G(5);
    G.clearMark();
    G.setEdge(0, 1, 3);
    G.setEdge(0, 3, 7);
    G.setEdge(0, 4, 8);
    G.setEdge(1, 2, 1);
    G.setEdge(1, 3, 4);
    G.setEdge(3, 2, 2);
    G.setEdge(4, 3, 3);
    //check all shortest paths for dijkstra function.
    EXPECT_EQ(3, G.dijkstra(0, 1));
    EXPECT_EQ(4, G.dijkstra(0, 2));
    EXPECT_EQ(7, G.dijkstra(0, 3));
    EXPECT_EQ(8, G.dijkstra(0, 4));

    EXPECT_EQ(INT_MAX, G.dijkstra(1, 0));
    EXPECT_EQ(1, G.dijkstra(1, 2));
    EXPECT_EQ(4, G.dijkstra(1, 3));
    EXPECT_EQ(INT_MAX, G.dijkstra(1, 4));

    EXPECT_EQ(INT_MAX, G.dijkstra(2, 0));
    EXPECT_EQ(INT_MAX, G.dijkstra(2, 1));
    EXPECT_EQ(INT_MAX, G.dijkstra(2, 3));
    EXPECT_EQ(INT_MAX, G.dijkstra(2, 4));

    EXPECT_EQ(INT_MAX, G.dijkstra(3, 0));
    EXPECT_EQ(INT_MAX, G.dijkstra(3, 1));
    EXPECT_EQ(2, G.dijkstra(3, 2));
    EXPECT_EQ(INT_MAX, G.dijkstra(3, 4));

    EXPECT_EQ(INT_MAX, G.dijkstra(4, 0));
    EXPECT_EQ(INT_MAX, G.dijkstra(4, 1));
    EXPECT_EQ(5, G.dijkstra(4, 2));
    EXPECT_EQ(3, G.dijkstra(4, 3));
  
}