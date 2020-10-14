// Test code for editor
#include "ECProj.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
using namespace  std;

int main(int argc, char *argv[])
{
    assert(argc == 2);   
    ECProj * wndTest = new ECProj(argv[1]); 
    wndTest->getView()->Show();
    delete wndTest;
    return 0;
}
