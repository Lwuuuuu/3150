#include <vector>
#include <set>
using namespace std;

bool IsSubString(const vector<char> &strInput, const vector<char> &strPattern )
{
// Concatenate two strings - 1) strConcatTo 2) strConcating.
// That is, you need to append the string strConcating to the end of strConcatTo.
// Result: strConcatTo passed to as input should contain the Concatenated string.
  bool found_subString = false;
  int k = strPattern.size();
  for (long unsigned int i = 0; i < strInput.size() - k + 1; ++i) {
    vector<char> subString(strInput.begin()+i, strInput.begin()+i+k);
    if (subString == strPattern) {
      found_subString = true;
      break;
    }
  }
  return found_subString ? true : false;
}

