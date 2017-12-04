#include <iostream>
#include <string>
#include <locale>

using namespace std;

// 1 entry means taken from string A
// 2 entry means taken from string B
int mat[1001][1001];

string getMerge(string &A, string &B, string &C);
int isMerge(string &A, string &B,string &C);
int isMerge(string &A, const int &i,string &B, const int &j, string &C);

int main(){
  string A = "hello";
  string B = "world";
  string C = "hewolrldlo";

  // string A = "zzzabc";
  // string B = "zzzacb";
  // string C = "zzzzzzacabbc";
  int i = isMerge(A,B,C);

  if(i){
    cout<<getMerge(A,B,C)<<endl;
  } else {
    cout<<"*** NOT A MERGE ***"<<endl;
  }


  for(int i=0;i<A.length()+1;i++){
    for(int j=0;j<B.length()+1;j++){
      if(j==B.length()){
        cout<<mat[i][j]<<endl;
      } else {
        cout<<mat[i][j];
      }
    }
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
    if(mat[i][j]==1){
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
    mat[i+1][j]=1;
    mat[i][j+1]=2;
    return isMerge(A,i+1,B,j,C)||isMerge(A,i,B,j+1,C);

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
