#include <iostream>
#include "hash.h"

using namespace std;

//Class GLOBAL
// List of primes optimal for hash table use
// from size 49,000 to 50,000,000
static const unsigned int primes[] = {196613, 393241, 786433,
1572869, 3145739, 6291469, 12582917, 25165843, 50331653};

//PUBLIC Member Function definitions

// The constructor initializes the hash table.
// Uses getPrime to choose a prime number at least as large as
// the specified size for the initial size of the hash table.
hashTable::hashTable(int size){
  capacity = getPrime(size);
  data.resize(capacity);
  filled = 0;
}

// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const string &key, void *pv){
  int i = hash(key);
  while(data.at(i).isOccupied){ // Linear Probing
    if(data.at(i).key == key) // if key already exists in hash table
      return 1;
    i++;
    if(i>capacity)
      i=0;
  }
  // insertion
  data.at(i).key = key,
  data.at(i).isOccupied = true,
  data.at(i).isDeleted = false,
  data.at(i).pv = pv;
  filled++;

  // rehashing condition: filled > capacity/2
  if((filled) > ((capacity)/2)){
    if(!rehash()) // rehash fails
      return 2;
  }
  return 0;
}

// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const string &key){
  if(findPos(key)>=0) // findPos returns -1 when key doesn't exist
    return true;
  return false;
}

// Get the pointer associated with the specified key.
// If the key does not exist in the hash table, return NULL.
// If an optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
void *hashTable::getPointer(const string &key, bool *b){
  int n = findPos(key);
  if(n>=0){
    if(b!=NULL)
      *b = true;
    return data.at(n).pv;
  }
  if(b!=NULL)
    *b = false;
  return NULL;
}

// Set the pointer associated with the specified key.
// Returns 0 on success,
// 1 if the key does not exist in the hash table.
int hashTable::setPointer(const string &key, void *pv){
  int n = findPos(key);
  if(n>=0){
    data.at(n).pv = pv;
    return 0;
  }
  return 1;
}

// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const string &key){
  int i = findPos(key);
  if(i>=0){
    data.at(i).isDeleted = true;
    data.at(i).isOccupied = false;
    return true;
  }
  return false;
}

// PRIVATE Member Function definitions
int hashTable::hash(const string &key){
  unsigned long hash = 5381;
  int c;
  int i=0;
  while ((c = key[i++]))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash%(capacity-1); //index ranging from 0->(capacity-1)
}

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const string &key){
  int i = hash(key); // set starting index at key's hash value
  int i0 = i;
  while(data.at(i).isOccupied){ // Linear Probing
    if(data.at(i).key == key) // if key already exists in hash table
      return i;
    i++;
    if(i>capacity)
      i=0;
    if(i==i0) // if looped through the entire table
      return -1;
  }
  return -1;
}

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash(){
  vector<hashItem> v; // new data table

  // p prime capacity of new table
  unsigned int p = getPrime(capacity*2);

  try{ // try to make new table double the size of current
    v.resize(p);
  } catch(bad_alloc){ // if memory allocation fails print an error
    cerr<<"ERROR: Failed rehash."<<endl;
    return false;
  }

  // Swap vectors v & data s.t. hashTable object
  // has blank table of double capacity.
  data.swap(v);
  capacity = p;
  filled = 0;

  vector<hashItem>::iterator itr;
  // iterate through old table, hashing items into new table
  for(itr = v.begin(); itr < v.end(); itr++){
    if(itr->isDeleted == false) // leave out lazy deletions
      insert(itr->key, itr->pv);
  }

  return true;
}

// Return a prime number at least as large as size.
// Uses a precomputed sequence of selected prime numbers.
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
