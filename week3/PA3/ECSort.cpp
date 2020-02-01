#include <vector>
#include <iostream>
using namespace std;

void ECSort(vector<int>& listInts)
{
  // Sort the numbers in the list
  int sz = listInts.size();
  if (sz > 1) {
    int idx = sz / 2;
    vector<int> left_array(&listInts[0], &listInts[0]+idx); //vector range func, pass 2 iterators of a vector and returns a copy of the elements in between the two iterators
    vector<int> right_array(&listInts[0]+idx, &listInts[0]+sz); //Split vector into right and left halves    
    ECSort(left_array);
    ECSort(right_array);
    long unsigned int i = 0;
    long unsigned int j = 0;
    long unsigned int k = 0;
    while (i < left_array.size() && j < right_array.size()) { //Merging algorithm between the left and right arrays
      if (left_array[i] <= right_array[j]) {
        listInts[k] = left_array[i];
        i++;
      }
      else {
        listInts[k] = right_array[j];
        j++;        
      }     
      k++;   
    }
    while (i < left_array.size()) { //Catches any remaining elements in the left/right array vectors
      listInts[k] = left_array[i];
      i++;
      k++;
    }
    while (j < right_array.size()) {
      listInts[k] = right_array[j];
      j++;
      k++;
    }    
  }

}

