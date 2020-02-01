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
  ifstream ipt(filename); //input stream 
  if ipt.is_open() {
    string user_input;
    while (getline(ipt, user_input) && user_input.length() > 0) { //Gets a line from the file 
      string temp;
      user_input += " "; //Add whitespace buffer so last number will not be missed
      for (auto x : user_input) {
          if (isspace(x) && temp.length() != 0) { //Whitespace found, means a number has been parsed, check length to disallow string of whitespaces
            listNumbers.push_back(stoi(temp)); //Convert to integer
            temp.clear(); //Clear for next number
          }
          else {
            if(!isspace(x)) //Prevents accumulation of whitespaces in temp string
              temp += x;
          }
      }
    }
    ipt.close();
  }
  else 
    cout << "Unable to open file." << endl;
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

