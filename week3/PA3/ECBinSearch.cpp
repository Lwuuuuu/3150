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
  if (listNumbers[current_index] == value) {  //Found number in list 
    return 0;
  }
  if (current_size == 1) //Unable to find number in list         
    return -1;
  if (listNumbers[current_index] < value) { //Check the right side of the vector 
    if (listNumbers.size() == 2) { //Cannot split vector anymore when size is 2, check the last remaining unchecked element of the vector
      if (listNumbers[0] != value)
        return -1;
    }
    else {
      const vector<int> right_array(&listNumbers[0]+current_index+1, &listNumbers[0]+current_size); //vector range func, pass 2 iterators of a vector and returns a copy of the elements in between the two iterators
      return ECBinarySearch(right_array, value);
    }
  } 
  else if (listNumbers[current_index] > value) { //Check the left side of the vector
    if (listNumbers.size() == 2) { //Cannot split vector anymore when size is 2, check the last remaining unchecked element of the vector
      if (listNumbers[0] != value)
        return -1;
    }
    else {
      const vector<int> left_array(&listNumbers[0], &listNumbers[0]+current_index); //vector range func, pass 2 iterators of a vector and returns a copy of the elements in between the two iterators
      return ECBinarySearch(left_array, value);
    }
  }   
  return -1;
}
