#ifndef _GRAPH_H
#define _GRAPH_H
#include <list>
#include <string>
#include <fstream>
#include "hash.h"
#include "heap.h"

class graph{
public:

  graph(void);

  // insert - Inserts an edge to the graph.
  //
  // Inserts the edge starting from node v going to node w,
  // with cost c.
  void insert(const std::string &v_id, const std::string &w_id, const int &cost);

  // pathLengthDijkstra - finds the shortest weighted path length
  //                      from node s to every other node in the graph
  //
  // Employs Dijkstra's algorithm using the heap class
  // as a priority queue.
  //
  // Returns:
  //    0 on success
  //    1 if the node s does not exist in the graph
  int pathLengthDijkstra(const std::string &s_id);

  void writePathLength(const std::string &outputfile);

private:

  // Each node has the following attributes:
  // name - string to identify the node
  // used for Dijkstra's:
  //    dv - cost of best path to get to given node.
  //    pv - pointer to previous node giving dv before current dv value.
  //    isKnown - bool used during the algorithm.
  // adjlist - list of edges leaving the node.
  class node {
  public:
    // Each edge has the following attributes:
    // w - pointer to the node that the edge goes to. (v->w)
    // cost - cost/weight of the edge
    class edge {
    public:
      node *w;
      int cost;
    };
    std::string id;
    int dv;
    node *pv;
    bool isKnown;
    std::list<edge> adjlist;
  };

  int size; // number of nodes the graph contains
  std::list<node *> *nodes; // list of nodes that the graph contains
  hashTable *mapping; // maps node names to nodes
};

#endif
