#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#define CAPACITY 1000000
#define NUM_NODES 100000
#define NUM_CMDS 10000000
#define KEY_RANGE 200000

using namespace std;

void genCommands(const string &outputfile);

int main(){
  srand(time(NULL));

  string outputfile;
  cout<<"Outputfile name: ";
  cin>> outputfile;
  genCommands(outputfile);

  return 0;
}

void genCommands(const string &outputfile){
  ofstream output;
  output.open(outputfile);
  string cap = to_string(CAPACITY);
  cout<<cap<<"";

  for(int i=0; i<NUM_CMDS; i++){
    int cmd = rand()%10+1;
    string c = to_string(cmd);
    int n;
    int key;
    string name;

    if(cmd>4){
      cout<<"1";
      n = rand()%NUM_NODES+1;
      key = rand()%KEY_RANGE+1;

      name = to_string(n);
      cout<<"string"<<name<<"";
      cout<<key;
    } else if(cmd==2){
      cout<<"2";
      n = rand()%NUM_NODES+1;
      key = rand()%KEY_RANGE+1;

      name = to_string(n);
      cout<<"string"<<name<<"";
      cout<<key;
    } else if(cmd==1){
      cout<<"3";
      n = rand()%NUM_NODES+1;
      name = to_string(n);
      cout<<"string"<<name;
    } else if(cmd==4||cmd==3){
      cout<<"4";
    }
  }
  cout<<"5"<<endl;
  output.close();
}
