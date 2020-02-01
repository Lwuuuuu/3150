#include <vector>
#include <iostream>
using namespace std;

void ECSort(vector<int>& listInts)
{
  // Sort the numbers in the list
  int sz = listInts.size();
  if (sz > 1) {
    int idx = sz / 2;
    vector<int> left_array(&listInts[0], &listInts[0]+idx);  
    vector<int> right_array(&listInts[0]+idx, &listInts[0]+sz);    
    ECSort(left_array);
    ECSort(right_array);
    long unsigned int i = 0;
    long unsigned int j = 0;
    long unsigned int k = 0;
    while (i < left_array.size() && j < right_array.size()) {
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
    while (i < left_array.size()) {
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

