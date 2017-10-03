#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>

using namespace std;

class heap{
public:
  heap();

private:

  class node { // An inner class within heap
  public:
    std::string id; // The id of this node
    int key; // The key of this node
    void *pData; // A pointer to the actual data
  };

  vector<node> data; // The actual binary heap
  hashTable *mapping; // maps ids to node pointers

  void percolateUp(int posCur);
  void percolateDown(int posCur);
  int getPos(node *pn);


};

#endif //_HASH_H
