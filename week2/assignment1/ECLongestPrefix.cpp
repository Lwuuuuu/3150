#include "ECLongestPrefix.h" 
#include <iostream>

using namespace std;

// Implement the longest prefix function here...
string ECLongestPrefix(int numStrings, const string arrayStrings[])
{
  // YW: this only serves as a starter code, which just print out the given array of strings
  // Replace with your own code here...
  string LongestPrefix = "";
  bool foundPrefix = false;
  if (numStrings == 0 || arrayStrings[0].size() == 0) 
    return LongestPrefix;
  if (numStrings == 1) {
    return arrayStrings[0];
  }
  string firstWord = arrayStrings[0];
  while (!foundPrefix) {
    for (int index = 0; index < firstWord.size(); ++index) {
      char currentChar = firstWord[index];
      for (int i=1; i<numStrings; ++i) {
        if (index < arrayStrings[i].size()) {
          if (arrayStrings[i][index] != currentChar) {
            foundPrefix = true;
            break;
          }
        }
        else { 
          foundPrefix = true;
          break;
        }
      }
      if (!foundPrefix) 
        LongestPrefix += currentChar;
      else {
        break;
      }
    }
    return LongestPrefix;
  }
  return LongestPrefix;
}

