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
  for (auto i : listTargets) {
    cout << "Looking for solution for " << i << endl;
    bool solution = false;
    for (auto j : listNumbers) { //Iterate through listNumbers and subtract val from listNumber from the target val then search listNumbers for that number
      cout << "Finding number to add together with " << j  << " " << "result becomes " << i << endl;
      if (ECBinarySearch(listNumbers, i - j) == 0) {//ECBinarySearch returns 0 if the number was present in the list of numbers 
        cout << "Found solution for " << i << "using the 2 numbers from num_list" << " " << (i - j) << " " << j << endl;
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


