#include "wList.H"
#include <iostream>
using namespace std;


void buildList(list<string> &modifyList) {
    string user_input;
    while (getline(cin, user_input) && user_input.length() > 0) {
        string temp;
        user_input += " ";
        for (auto x : user_input) {
            if (isspace(x)) {
                modifyList.push_back(temp);
                temp.clear();
            }
            else {
                temp += x;
            }
        }
    }
}

int main() {
    list<string> res;
    buildList(res);
    for (auto x : res) { 
        cout << x << endl;
    }
    return 0;
}
