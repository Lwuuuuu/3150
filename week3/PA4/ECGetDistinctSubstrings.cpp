#include <set>
#include <vector>
using namespace std;

void GetDistinctSubstrings(const vector<char> & strInput, int k, set< std::vector<char> > &setUniqueSubstrings  )
{
// find the set of all distinct length-k substrings in a given string.
// store the set of distinct substrings of length-k 
// in strInput into setUniqueSubstrings
  for(long unsigned int i = 0; i < strInput.size() - k + 1; ++i) {
    vector<char> subString(strInput.begin()+i, strInput.begin()+i+k);
    setUniqueSubstrings.insert(subString);
  }
}

