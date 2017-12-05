#include <iostream>
#include <string>
#include <locale>
#include <fstream>

using namespace std;

// 1 entry means taken from string A
// 2 entry means taken from string B
int mat[1001][1001];
int known[1001][1001];

void parseFile(const string &inputfile);
string getMerge(string &A, string &B, string &C);
int isMerge(string &A, string &B,string &C);
int isMerge(string &A, const int &i,string &B, const int &j, string &C);

int main(){
  string inputfile, line;

  cout<<"Enter name of input file: ";
  cin>>inputfile;

  ifstream input(inputfile.c_str());
  if(input.is_open()){
    int count = 1;
    string A,B,C;
    while(getline(input, line)){
      switch(count){
        case 1:
          A = line;
          count++;
          break;
        case 2:
          B = line;
          count++;
          break;
        case 3:
          C = line;
          isMerge(A,B,C);
          if(mat[A.length()][B.length()]){
            cout<<getMerge(A,B,C)<<endl;
          } else {
            cout<<"*** NOT A MERGE ***"<<endl;
          }
          for(int i=0;i<A.length()+1;i++){
            for(int j=0;j<B.length()+1;j++){
              if(j==B.length()){
                cout<<mat[i][j]<<endl;
                mat[i][j]=0;
                known[i][j]=0;
              } else {
                cout<<mat[i][j];
                mat[i][j]=0;
                known[i][j]=0;
              }
            }
          }
          count=1;
          break;
      }
    }
    input.close();
  } else {
    cout<<"Unable to open file"<<endl;
  }
  return 0;
}

string getMerge(string &A, string &B, string &C){
  locale loc;
  int i = A.length();
  int j = B.length();
  if(mat[i][j]==0){
    return "\nya done messed up somewhere\n";
  }
  for(int k=C.length()-1;k>=0;k--){
    if(mat[i][j]==1||mat[i][j]==3){
      C[k] = toupper(C[k],loc);
      i--;
    } else {
      j--;
    }
  }
  return C;
}

// returns 0 on invalid invalid merge
// 1 on valid merge
int isMerge(string &A, string &B, string &C){
  return isMerge(A,0,B,0,C);
}

int isMerge(string &A, const int &i, string &B, const int &j, string &C){
  if(i>A.length() && j>B.length()){
    return 1;
  }
  if(A[i]==C[i+j] && B[j]==C[i+j]){
    if(!known[i+1][j] && !known[i][j+1]){
      known[i+1][j]=1;
      mat[i+1][j]=1;
      known[i][j+1]=1;
      mat[i][j+1]=2;
      return isMerge(A,i+1,B,j,C)||isMerge(A,i,B,j+1,C);

    } else if(!known[i+1][j]){
      known[i+1][j]=1;
      mat[i+1][j]=1;
      return isMerge(A,i+1,B,j,C);

    } else if(!known[i][j+1]){
      known[i][j+1]=1;
      mat[i][j+1]=2;
      return isMerge(A,i,B,j+1,C);
    }
  } else if(A[i]==C[i+j]){
    mat[i+1][j]=1;
    return isMerge(A,i+1,B,j,C);

  } else if(B[j]==C[i+j]){
    mat[i][j+1]=2;
    return isMerge(A,i,B,j+1,C);
  } else if(A[i]!=C[i+j] && B[j]!=C[i+j]){
    return 0;
  }
}
