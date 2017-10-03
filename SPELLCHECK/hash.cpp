#include <iostream>
#include "hash.h"

// NOTE: MUST use ::hash() to use hash function defined in hash.h
// otherwise hash() conflicts with c++ library hash function
using namespace std;

//Class GLOBAL
// List of primes optimal for hash table use
// from size 49,000 to 50,000,000
static const unsigned int primes[] = {196613, 393241, 786433,
1572869, 3145739, 6291469, 12582917, 25165843, 50331653};

//PUBLIC Member Function definitions
hashTable::hashTable(int size){
  this->capacity = this->getPrime(size);
  this->data.resize(capacity);
  this->filled = 0;
}

int hashTable::insert(const string &key, void *pv){
  int i = this->hash(key);
  while(this->data.at(i).isOccupied){ // Linear Probing
    if(this->data.at(i).key == key) // if key already exists in hash table
      return 1;
    i++;
  }
  // insertion
  data.at(i).key = key,
  data.at(i).isOccupied = true,
  data.at(i).isDeleted = false,
  data.at(i).pv = pv;
  this->filled++;

  // rehashing condition: filled > capacity/2
  if((this->filled) > ((this->capacity)/2)){
    if(!this->rehash()) // rehash fails
      return 2;
  }
  return 0;
}

bool hashTable::contains(const string &key){
  if(findPos(key)>=0) // findPos returns -1 when key doesn't exist
    return true;
  return false;
}

// Yet to be implemented
void *hashTable::getPointer(const string &key, bool *b){return b;}
int setPointer(const string &key, void *pv){return 0;}
bool hashTable::remove(const string &key){return false;}

// PRIVATE Member Function definitions
int hashTable::hash(const string &key){
  unsigned long hash = 5381;
  int c;
  int i=0;
  while ((c = key[i++]))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash%(this->capacity-1); //index ranging from 0->(capacity-1)
}

int hashTable::findPos(const string &key){
  int i = this->hash(key); // set starting index at key's hash value
  while(this->data.at(i).isOccupied){ // Linear Probing
    if(this->data.at(i).key == key) // if key already exists in hash table
      return i;
    i++;
  }
  return -1;
}

bool hashTable::rehash(){
  vector<hashItem> v; // new data table

  // p prime capacity of new table
  unsigned int p = this->getPrime(this->capacity*2);

  try{ // try to make new table double the size of current
    v.resize(p);
  } catch(bad_alloc){ // if memory allocation fails print an error
    cerr<<"ERROR: Failed rehash."<<endl;
    return false;
  }

  // Swap vectors v & data s.t. hashTable object
  // has blank table of double capacity.
  this->data.swap(v);
  this->capacity = p;
  this->filled = 0;

  vector<hashItem>::iterator itr;
  // iterate through old table, hashing items into new table
  for(itr = v.begin(); itr < v.end(); itr++){
    if(itr->isDeleted == false) // leave out lazy deletions
      this->insert(itr->key, itr->pv);
  }

  return true;
}

unsigned int hashTable::getPrime(int size){
  unsigned int p = primes[0]; //initialize p to first prime in array
  int i = 0;
  int n = sizeof(primes)/sizeof(primes[0])-1; //last index of primes array
  if(size < primes[n]){ //to prevent index i going beyond array bounds
    while(size>primes[i++]) //brings p to first prime larger than size
      p = primes[i];
    return p;
  }
  return -1;
}
