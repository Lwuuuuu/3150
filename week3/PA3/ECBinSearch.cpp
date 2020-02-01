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
  int current_size = listNumbers.size();
  int current_index = current_size / 2;
  if (listNumbers[current_index] == value) {  
    return 0;
  }
  if (current_size == 1)        
    return -1;
  if (listNumbers[current_index] < value) {
    if (listNumbers.size() == 2) { 
      if (listNumbers[0] != value)
        return -1;
    }
    else {
      const vector<int> right_array(&listNumbers[0]+current_index+1, &listNumbers[0]+current_size);
      return ECBinarySearch(right_array, value);
    }
  } 
  else if (listNumbers[current_index] > value) {
    if (listNumbers.size() == 2) {
      if (listNumbers[0] != value)
        return -1;
    }
    else {
      const vector<int> left_array(&listNumbers[0], &listNumbers[0]+current_index);  
      return ECBinarySearch(left_array, value);
    }
  }   
  return -1;
}
