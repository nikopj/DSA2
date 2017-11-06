#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "hash.h"
#include "heap.h"
#include "graph.h"

using namespace std;

graph::graph(){
  size = 0;
  mapping = new hashTable(1);
  nodes = new list<node *>;
}

void graph::insert(const string &v_id, const string &w_id, const int &cost){
  node *v;
  node *w;
  node::edge vw;

  // initialization of nodes v & w
  if(!mapping->contains(v_id)){
    v = new node;
    v->id = v_id;
    nodes->push_back(v);
    mapping->insert(v_id, v);
    size++;
  } else {
    v = static_cast<node *> (mapping->getPointer(v_id));
  }
  if(!mapping->contains(w_id)){
    w = new node;
    w->id = w_id;
    nodes->push_back(w);
    mapping->insert(w_id, w);
    size++;
  } else {
    w = static_cast<node *> (mapping->getPointer(w_id));
  }

  // setting of edge node to w and pushing to v's adjacency list
  vw.w = w;
  vw.cost = cost;
  v->adjlist.push_back(vw);
}

int graph::pathLengthDijkstra(const string &s_id){
  if(!mapping->contains(s_id))
    return 1;
  heap h(size);
  int known = 0;

  list<node *>::const_iterator itr;
  for(itr = nodes->begin(); itr!=nodes->end(); itr++){
    (*itr)->dv = 2147483647; // limit of signed int ie. infinity
    (*itr)->isKnown = false;
    (*itr)->pv = NULL;
    h.insert((*itr)->id, 2147483647, *itr);
  }
  h.setKey(s_id, 0);
  node *s = static_cast<node *> (mapping->getPointer(s_id));
  s->pv = NULL;
  s->dv = 0;

  while(known<size){
    node **ppn;
    node *pn;
    pn = new graph::node;
    ppn = &pn;

    h.deleteMin(NULL, NULL, ppn);
    pn = *ppn;
    pn->isKnown = true;
    known++;

    list<node::edge>::const_iterator jtr;
    for(jtr = pn->adjlist.begin(); jtr!=pn->adjlist.end(); jtr++){
      if(pn->dv + jtr->cost < jtr->w->dv){
        jtr->w->dv = pn->dv + jtr->cost;
        h.setKey(jtr->w->id, jtr->w->dv);
        jtr->w->pv = pn;
      }
    }
  }

  return 0;
}

void graph::writePathLength(const string &outputfile){
  ofstream output;
  output.open(outputfile);

  list<node *>::const_iterator itr;
  for(itr = nodes->begin(); itr!=nodes->end(); itr++){
    string path;
    output<<(*itr)->id<<": ";

    if((*itr)->pv==NULL && (*itr)->dv==2147483647){
      output<<"NO PATH"<<endl;

    } else {
      output<<(*itr)->dv<<" ";

      node *pn;
      pn = *itr;

      while(pn->pv!=NULL){
        path.insert(0, ", "+pn->id);
        pn = pn->pv;
      }
      path.insert(0, pn->id);

      path.insert(0, "[");
      path.push_back(']');

      output<<path<<endl;
    }
  }
  output.close();
}
