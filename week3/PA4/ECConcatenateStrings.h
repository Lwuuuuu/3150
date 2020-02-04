#ifndef ECCONCATENATESTRINGS_H

#define ECCONCATENATESTRINGS_H

#include <vector>

// Concatenate two strings - 1) strConcatTo 2) strConcating.
// That is, you need to append the string strConcating to the end of strConcatTo.
// Result: strConcatTo passed to as input should contain the Concatenated string.
void ConcatenateStrings( std::vector<char> &strConcatTo, 
  const std::vector<char> &strConcating  );
#endif  // ECCONCATENATESTRINGS_H
