#ifndef _GRAPH_H
#define _GRAPH_H
#include <list>
#include "hashTable.h"
#include "heap.h"

class graph(){
public:

private:

  class node {
  public:
    string id;
    int key;
  }
  // Adjacency List of verticies.
  // Each verticie is at the start of a linked list
  // of associated edges.
  list<list<node> *> adjList;
  hashTable *mapping; // maps verticie names to nodes in adjList
  heap *priorityq; // priority que for shortest path algorithm
};

#endif
