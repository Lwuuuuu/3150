#include <iostream>
#include "ECArrayofStrings.h" 

using namespace std;

ECArrayofStrings::ECArrayofStrings()
{
}

ECArrayofStrings::~ECArrayofStrings()
{
  // your code goes here
}

void ECArrayofStrings :: AddString( const string &strToAdd )
{
  // your code goes here
  vec.push_back(strToAdd);
}

int ECArrayofStrings :: GetNumofStrings() const
{
  // your code goes here
  return vec.size();
}

int ECArrayofStrings :: GetMaxLen() const
{
  // your code goes here
  int max_len = 0; 
  for (auto x : vec) {
    if (x.size() > max_len)
      max_len = x.size();
  }
  return max_len;
}

string ECArrayofStrings :: GetLongestCommonPrefix() const
{
  // your code goes here
  if (vec.size() == 0)
    return string("");
  int f_string = vec[0];
  res = string();
  for (int i = 0; f_string.size(); ++i) {
    for (auto x : vec) {
      if (x[i] != f_string[i]) {
        return res;
      }
    }
    res += f_string[i];
  }
}

string ECArrayofStrings :: Concatnate() const
{
  // your code goes here
}

void ECArrayofStrings:: Dump() const
{
  // your code goes here
}

string ECArrayofStrings :: GetLongestCommonPrefixofTwo(const string &str1, const string &str2) const
{
  // your code goes here
}


