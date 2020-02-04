#include <iostream>
#include <vector>
#include <set>

#include "ECConcatenateStrings.h"
#include "ECGetDistinctSubstrings.h"
#include "ECIsSubString.h"

using namespace std;

void printvectchar(vector<char> &vc)
{
  for(unsigned int i=0;i<vc.size();i++)
  {
      cout<<vc[i];
  }
}

void test_DistinctSubstring(void)
    {
    set<vector<char>> subStrings;
    int num=2;
    string s1="string1";
    vector<char> string1(s1.begin(),s1.end());
    GetDistinctSubstrings(string1,num,subStrings);
    set<vector<char>>::iterator it;
    int i=0;
    for(it = subStrings.begin();it != subStrings.end();it++)
    { 
      string strIn((*it).begin(),(*it).end());
      cout<<strIn<<" ";
      i++;
    }
    cout<<endl;
    }

void test_concat(void)
    {
    set<vector<char>> subStrings;
    string s1="String1To";
    string s2="String2";
    vector<char> strConcatTo(s1.begin(),s1.end());
    vector<char> strConcating(s2.begin(),s2.end());
    ConcatenateStrings(strConcatTo,strConcating);
    string strIn(strConcatTo.begin(),strConcatTo.end());
    cout<<strIn<<endl;
    }
    

void test_IsSubString(void)
    {
    set<vector<char>> subStrings;
    string s1="Split";
    string s2="Line";
    vector<char> strContainer(s1.begin(),s1.end());
    vector<char> strSub(s2.begin(),s2.end()); 
    cout<<s1<<endl;
    cout<<s2<<endl;
    cout<<"Result: "<<IsSubString(strContainer,strSub)<<endl;
    }

int main(int argc, char **argv)
    {
       test_DistinctSubstring();
       test_concat();
       test_IsSubString();
       
       return 0;
    }
