#include <iostream>
#include <fstream>
#include <string>
#include <time.h> // to check elapsed time of certain functions
#include <algorithm> // to ease string lowercase conversion
#include "hash.h"

using namespace std;

// Loads dictionary file into a hash table which is returned
hashTable loadDictionary(const string &dictionary);
// Reads input file character by character,
// processes commands, and writes to output file
void spellCheck(hashTable &htable, const string &inputfile, const string &outputfile);

int main(){
  string dictionary, inputfile, outputfile;
  clock_t t;

  cout<<"Enter name of dictionary: ";
  cin>>dictionary;

  t = clock();
  hashTable h = loadDictionary(dictionary);
  t = clock() - t;

  double timeDiff = ((double)(t))/CLOCKS_PER_SEC;

  cout<<"Total time (in seconds) to load dictionary: "<<timeDiff<<"\n";

  cout<<"Enter name of input file: ";
  cin>>inputfile;
  cout<<"Enter name of output file: ";
  cin>>outputfile;

  t = clock();
  spellCheck(h, inputfile, outputfile);
  t = clock()-t;

  timeDiff = ((double)(t))/CLOCKS_PER_SEC;

  cout<<"Total time (in seconds) to check document: "<<timeDiff<<"\n";

  return 0;
}

hashTable loadDictionary(const string &dictionary){
  string line;
  ifstream input(dictionary);

  hashTable htable(100000);

  // Opens input file, safeguards against failure of opening
  if(input.is_open()){
    while(getline(input, line)){
      bool is_valid = true;

      for(int i=0; i<line.length(); i++){
        if(!(('A'<=line[i]&&line[i]<='Z')||('a'<=line[i]&&line[i]<='z')||line[i]=='-'||line[i]=='\''))
          is_valid = false;
      }
      if(is_valid){
        string key = line.substr(0, line.length());
        // to lowercase conversion using algorithm library
        transform(key.begin(), key.end(), key.begin(),::tolower);
        htable.insert(key);
      }
    }
    input.close();
  } else
    cout<<"Unable to open file"<<endl;

  return htable;
}

void spellCheck(hashTable &htable, const string &inputfile, const string &outputfile){
  int line_count = 1;
  int letter_count = 0;
  char c;
  string word(20, 'x'); //initialize size 20 word (to garbage values)
  bool check_spelling = true;

  ifstream input(inputfile);
  ofstream output;

  // Opens input file, safeguards against failure of opening
  if(input.is_open()){
    output.open(outputfile);

    // Iterates line by line through input file
    while(input.get(c)){

      // valid character condition
      if(('0'<=c&&c<='9')||('A'<=c&&c<='Z')||('a'<=c&&c<='z')||c=='-'||c=='\''){
        // words containing these don't need to be checked
        if('0'<=c&&c<='9')
          check_spelling = false;

        word[letter_count++] = c;

        if(letter_count>=21){ // word too long
          if(letter_count==21){
            string longword = word.substr(0,20);
            // to lowercase conversion using algorithm library
            transform(longword.begin(), longword.end(), longword.begin(),::tolower);

            output<<"Long word at line "<<line_count<<", starts: "
            <<longword<<"\n";
          }
          check_spelling = false;
        }
      } else {
        if(check_spelling&&letter_count!=0){ //invalid character condition reached
          string key = word.substr(0, letter_count);
          // to lowercase conversion using algorithm library
          transform(key.begin(), key.end(), key.begin(),::tolower);

          if(!htable.contains(key))
            output<<"Unknown word at line "<<line_count<<": "<<key<<"\n";
        }
        // reset variables for next word
        letter_count = 0;
        check_spelling = true; // default state is to check spelling
      }

      if(c=='\n')
        line_count++;
    }

    input.close();
    output.close();
  } else
    cout<<"Unable to open file"<<endl;
}
