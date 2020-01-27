#include "wList.H"
#include <iostream>
// #include "wList.cpp"
using namespace std;
int main()
{
   list<string> * res = buildList();
    for(auto x : *res)
      cout << x << endl;
   delete res;
   return 0;
}
