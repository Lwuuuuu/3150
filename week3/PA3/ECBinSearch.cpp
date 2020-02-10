#include <vector>
#include <algorithm> 
#include <iostream>
using namespace std;


// Your first C++ program is here...
int ECBinarySearch(const vector<int> &listNumbers, int value)
{
  // input list of numbers comes as listNumbers vector
  // You need to implement binary search of "value" over this list; 
  // return the position (i.e., array index) of the vector that matches "value"; 
  // or return -1 if not found.
  int right = listNumbers.size();
  int left = 0;
  while (left <= right) {
    int middle = left + (right - left) / 2;
    if (listNumbers[middle] == value) 
      return middle;
    if (listNumbers[middle] < value)
      left = middle + 1; 
    else 
      right = middle - 1;
  } 
  return -1;
}
