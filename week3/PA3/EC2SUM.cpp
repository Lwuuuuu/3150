#include <vector>
#include "ECSort.cpp"
#include "ECBinSearch.cpp"
using namespace std;

void EC2SUM(vector<int> &listNumbers, const vector<int> &listTargets, vector<bool> &list2SUMRes )
{
  // for each number x = listTargets[i], if there are two numbers 
  // in listNumbers that add up to x, then list2SUMres[i]=true 
  // otherwise, list2SUMRes[i]=false
  ECSort(listNumbers); //Start by sorting the list, necessary for mergesort 
  for (long unsigned int i = 0; i < listTargets.size(); ++i) {
    bool solution = false;
    for (long unsigned int j = 0; j < listNumbers.size(); ++j) { //Iterate through listNumbers and subtract val from listNumber from the target val then search listNumbers for that number
      vector<int> removed_current = listNumbers;
      removed_current.erase(removed_current.begin() + j); //Cannot use the current listNumber value twice ie) if listNumbers contains 2 and 1 and listTargets contains 4, cannot use 2 twice to make 4
      if (ECBinarySearch(removed_current, listTargets[i] - listNumbers[j]) == 0) {//ECBinarySearch returns 0 if the number was present in the list of numbers 
        solution = true;
        break;
      }
    }
    if (solution == true) {
      list2SUMRes.push_back(true);
    }
    else {
      list2SUMRes.push_back(false);    
    }
  }
}


