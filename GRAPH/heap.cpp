#include <vector>
#include <string>
#include <iostream>
#include <cmath> //BUGTESTING
#include "heap.h"
#include "hash.h"

using namespace std;

// heap - The constructor allocates space for the nodes of the heap
// and the mapping (hash table) based on the specified capacity
//
heap::heap(int capacity){
  data.resize(capacity+1);
  mapping = new hashTable(capacity*2);
  size = 0;
  this->capacity = capacity;
}

// insert - Inserts a new node into the binary heap
//
// Inserts a node with the specified id string, key,
// and optionally a pointer. The key is used to
// determine the final position of the new node.
//
// Returns:
//   0 on success
//   1 if the heap is already filled to capacity
//   2 if a node with the given id already exists (but the heap
//     is not filled to capacity)
//
int heap::insert(const string &id, int key, void *pv){
  if(size>=capacity)
    return 1;
  if(mapping->contains(id)){
    if(size==0){
      cerr<<"Insert_ERROR: mapping should contain no IDs!"<<endl;
    }
    return 2;
  }
  size++;
  data.at(size).id = id;
  data.at(size).key = key;
  data.at(size).pData = pv;
  if(mapping->insert(id, &data.at(size))){
    cerr<<"Insert_ERROR: Failed insert."<<endl;
  }
  if(key<data.at(size/2).key){
    percolateUp(size);
  }
  return 0;
}

// setKey - set the key of the specified node to the specified value
//
// I have decided that the class should provide this member function
// instead of two separate increaseKey and decreaseKey functions.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
//
int heap::setKey(const string &id, int key){
  bool  b;
  node *pn = static_cast<node *> (mapping->getPointer(id, &b));
  // item with given id doesn't exist in mapping
  if(!b)
    return 1;
  int i = getPos(pn);
  // setting of key
  data.at(i).key = key;
  if(size==1){
    return 0;
  }
  percolate(i);

  return 0;
}

// deleteMin - return the data associated with the smallest key
//             and delete that node from the binary heap
//
// If pId is supplied (i.e., it is not NULL), write to that address
// the id of the node being deleted. If pKey is supplied, write to
// that address the key of the node being deleted. If ppData is
// supplied, write to that address the associated void pointer.
//
// Returns:
//   0 on success
//   1 if the heap is empty
//
int heap::deleteMin(string *pId, int *pKey, void *ppData){
  if(size==0)
    return 1;
  // get min values
  if(pId!=NULL)
    *pId = data[1].id;
  if(pKey!=NULL)
    *pKey = data[1].key;
  if(ppData!=NULL)
    *(static_cast<void **> (ppData)) = data[1].pData;

  if(!mapping->hashTable::remove(data[1].id)){
    cerr<<"Dmin_ERROR: ID not in hashtable!"<<endl;
  }
  // don't move nodes if this was the only item
  if(size==1){
    size--;

    return 0;
  }
  // move last item to root and percolate down
  data[1].id = data.at(size).id;
  data[1].key = data.at(size).key;
  data[1].pData = data.at(size).pData;
  if(mapping->setPointer(data[1].id, &data[1])){
    cerr<<"Dmin_ERROR: Pointer not set!"<<endl;
  }
  size--;
  percolateDown(1);
  return 0;
}

// remove - delete the node with the specified id from the binary heap
//
// If pKey is supplied, write to that address the key of the node
// being deleted. If ppData is supplied, write to that address the
// associated void pointer.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
//
int heap::remove(const string &id, int *pKey, void *ppData){
  bool b;
  node *pn = static_cast<node *> (mapping->getPointer(id, &b));

  // item with given id doesn't exist in mapping
  if(!b)
    return 1;

  int i = getPos(pn);
  // store values of node to be removed
  if(pKey!=NULL)
    *pKey = data[i].key;
  if(ppData!=NULL)
    *(static_cast<void **> (ppData)) = data[i].pData;

  if(!mapping->hashTable::remove(data[i].id)){
    cerr<<"Remove_ERROR: ID not in hashtable!"<<endl;
  }
  if(size==0){
    cerr<<"Remove_ERROR: Size == 0! Removing non-existent node!\n"
        <<"\tID to remove: "<<id<<"\n"
        <<"\tID found: "<<data[i].id<<endl;
  }
  // don't move nodes around if this is the or last item
  if(size==1 || i==size){
    size--;
    return 0;
  }
  // move last item to position i, percolate
  data[i].id = data.at(size).id;
  data[i].key = data.at(size).key;
  data[i].pData = data.at(size).pData;

  if(mapping->setPointer(data[i].id, &data[i])){
    cerr<<"Remove_ERROR: Pointer not set!"<<endl;
  }
  size--;
  percolate(i);
  return 0;
}

// Decides whether to percolate up or down
void heap::percolate(int posCur){
  if(posCur>1 && (data.at(posCur).key<data.at(posCur/2).key)){
    percolateUp(posCur);
  } else if((2*posCur<=size && data.at(posCur).key>data.at(2*posCur).key)||
          (2*posCur+1<=size && data.at(posCur).key>data.at(2*posCur+1).key)){
    percolateDown(posCur);
  }
}

// Moves node at current position up
// through tree if key < parents key.
// Stops at root
void heap::percolateUp(int posCur){
  // hole method of percolate:
  // copy contents of node to percolate into temporary storage.
  string temp_id = data.at(posCur).id;
  int temp_key = data.at(posCur).key;
  void *temp_pData = data.at(posCur).pData;

  while(temp_key<data.at(posCur/2).key && posCur!=1){
    // moving parent node data down
    data.at(posCur).id = data.at(posCur/2).id;
    data.at(posCur).key = data.at(posCur/2).key;
    data.at(posCur).pData = data.at(posCur/2).pData;
    if(mapping->setPointer(data.at(posCur).id, &data.at(posCur))){
      cerr<<"PercUp_ERROR: Pointer not set!"<<endl;
    }
    // hole moves one node up
    posCur = posCur/2;
  }
  // HOP satisfied
  data.at(posCur).id = temp_id;
  data.at(posCur).key = temp_key;
  data.at(posCur).pData = temp_pData;
  if(mapping->setPointer(temp_id, &data.at(posCur))){
    cerr<<"PercUp_ERROR: Pointer not set!"<<endl;
  }
}

// Moves node at current poisition down
// through tree if key > either children's key.
// Stops when node has no children.
void heap::percolateDown(int posCur){
  // hole method of percolate:
  // copy contents of node to percolate into temporary storage.
  string temp_id = data.at(posCur).id;
  int temp_key = data.at(posCur).key;
  void *temp_pData = data.at(posCur).pData;

  while((2*posCur<=size && temp_key>data.at(2*posCur).key)||
      (2*posCur+1<=size && temp_key>data.at(2*posCur+1).key)){
    // check if node swap occurs with left or right child
    int n;
    if(2*posCur+1>size){ // no right child
      n = 0;
    } else if(data.at(2*posCur).key<=data.at(2*posCur+1).key){
      n = 0;
    } else {
      n = 1;
    }

    // move child node up to parent
    data.at(posCur).id = data.at(2*posCur+n).id;
    data.at(posCur).key = data.at(2*posCur+n).key;
    data.at(posCur).pData = data.at(2*posCur+n).pData;
    if(mapping->setPointer(data.at(posCur).id, &data.at(posCur))){
      cerr<<"PercDown_ERROR: Pointer not set!"<<endl;
    }
    // hole moves one node up
    posCur = 2*posCur+n;
  }
  // HOP satisfied
  data.at(posCur).id = temp_id;
  data.at(posCur).key = temp_key;
  data.at(posCur).pData = temp_pData;
  if(mapping->setPointer(temp_id, &data.at(posCur))){
    cerr<<"PercDown_ERROR: Pointer not set!"<<endl;
  }
}

// returns index of node in the heap array given a pointer to it.
// node pointer generally comes from a hashtable.
int heap::getPos(node *pn){
  int pos = pn - &data[0];
  return pos;
}
