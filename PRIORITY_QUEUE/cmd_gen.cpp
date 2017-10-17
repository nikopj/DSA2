#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#define CAPACITY 20
#define NUM_NODES 15
#define NUM_CMDS 10000
#define KEY_RANGE 20

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
  output<<cap<<"\n";

  for(int i=0; i<NUM_CMDS; i++){
    int cmd = rand()%10+1;
    string c = to_string(cmd);
    int n;
    int key;
    string name;

    if(cmd>4){
      output<<"1\n";
      n = rand()%NUM_NODES+1;
      key = rand()%KEY_RANGE+1;

      name = to_string(n);
      output<<"string"<<name<<"\n";
      output<<key<<endl;
    } else if(cmd==2){
      output<<"2\n";
      n = rand()%NUM_NODES+1;
      key = rand()%KEY_RANGE+1;

      name = to_string(n);
      output<<"string"<<name<<"\n";
      output<<key<<endl;
    } else if(cmd==1){
      output<<"3\n";
      n = rand()%NUM_NODES+1;
      name = to_string(n);
      output<<"string"<<name<<endl;
    } else if(cmd==4||cmd==3){
      output<<"4"<<endl;
    }
  }
  output<<"5\n"<<endl;
  output.close();
}
