#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "graph.h"

using namespace std;

graph loadGraph(const string &inputfile);
void writePathLength(graph g, const string &outputfile);

int main(){
  string inputfile, vertex_id, outputfile;
  int b = 1;
  clock_t t;

  cout<<"Enter name of graph file: ";
  cin>>inputfile;

  graph g = loadGraph(inputfile);

  while(b==1){
    cout<<"Enter a valid vertex id for the starting vertex: ";
    cin>>vertex_id;
    t = clock();
    b = g.pathLengthDijkstra(vertex_id);
    t = clock() - t;
    if(b==1){
      cout<<"ERROR: vertex id does not exist."<<endl;
    }
  }

  double timeDiff = ((double)(t))/CLOCKS_PER_SEC;

  cout<<"Total time (in seconds) to apply Dijkstra's algorithm: "<<timeDiff<<"\n";
  cout<<"Enter name of output file: ";
  cin>>outputfile;

  g.writePathLength(outputfile);

  return 0;
}

graph loadGraph(const string &inputfile){
  string line;
  ifstream input(inputfile);

  graph g;

  if(input.is_open()){
    while(getline(input, line)){
      string v_id, w_id, cost;
      int i, c;

      i = line.find(" ");
      v_id = line.substr(0,i);
      line = line.substr(i+1);

      i = line.find(" ");
      w_id = line.substr(0,i);
      line = line.substr(i+1);

      i = line.find("\n");
      cost = line.substr(0, i);

      c = atoi(cost.c_str());

      g.insert(v_id, w_id, c);
    }
    input.close();
  } else {
    cout<<"Unable to open file"<<endl;
  }
  return g;
}
