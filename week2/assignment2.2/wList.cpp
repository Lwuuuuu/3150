#include "wList.H"
#include <iostream>
using namespace std;


list<string> * buildList() {
    list<string> * res = new list<string>();
    string user_input;
    while (getline(cin, user_input) && user_input.length() > 0) {
        string temp;
        user_input += " ";
        for (auto x : user_input) {
            if (isspace(x)) {
                res->push_back(temp);
                temp.clear();
            }
            else {
                temp += x;
            }
        }
    }
    return res;
}
