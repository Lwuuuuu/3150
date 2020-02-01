#include "EC2SUM.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;

// File I/O
static void ReadIntsFromFile(const char *filename, vector<int> &listNumbers)
{
  // Your code here
  ifstream ipt(filename);
  string user_input;
  while (getline(ipt, user_input) && user_input.length() > 0) {
    string temp;
    user_input += " ";
    for (auto x : user_input) {
        if (isspace(x) && temp.length() != 0) {
          listNumbers.push_back(stoi(temp));
          temp.clear();
        }
        else {
          if(!isspace(x))
            temp += x;
        }
    }
  }
  ipt.close();
}

// main function
int main( int argc, const char* argv[] )
{
  // 
  if( argc != 3 )
  {
    // Usage: ./2SUM <number-file> <target-file>
    cout << "Error.  Usage:  ./2SUM <number-file> <target-file> \n";
    exit(1);  
  }

  // read in integers from the first file
  vector<int> listNumbers;
  ReadIntsFromFile( argv[1], listNumbers );

  // read in integers from the seconf file
  vector<int> listTargets;
  ReadIntsFromFile( argv[2], listTargets );
  // 
  vector<bool> listResults;
  EC2SUM(listNumbers, listTargets, listResults);
  // dump out results
  cout << "Number of integers in list: " << listNumbers.size() << endl;
  cout << "Nummber of integers to search: " << listTargets.size() << endl;
  for(int i=0; i<(int)listTargets.size(); ++i)
  {
    cout << "Target " << listTargets[i] << ":\t";
    if( listResults[i] )
    {
      cout << "FOUND\n";
    }
    else
    {
      cout << "NOT FOUND\n";
    }
  } 

}

