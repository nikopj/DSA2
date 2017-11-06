#include <string>
#include <iostream>
#include <list>

using namespace std;

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

int main(){
  list<node *> nodes;
  node *v;
  v = new node;
  v->id = "fuck";

  nodes.push_back(v);

  return 0;
}
