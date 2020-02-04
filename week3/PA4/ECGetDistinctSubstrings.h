#ifndef ECGETDISTINCTSUBSTRINGS_H
#define ECGETDISTINCTSUBSTRINGS_H

#include <vector>
#include <set>
// find the set of all distinct length-k substrings in a given string.
// store the set of distinct substrings of length-k 
// in strInput into setUniqueSubstrings
void GetDistinctSubstrings( const std::vector<char> & strInput,
  int k, std::set< std::vector<char> > &setUniqueSubstrings  );

#endif  // ECGETDISTINCTSUBSTRINGS_H
