#ifndef ECCompose_h
#define ECCompose_h
#include <vector>
#include <string>
#include "ECComp.h"
using namespace std;

class ECParagraph;

class ECCompositor {
    public:
        ECCompositor(int numCols) : _numCols(numCols) {}
        virtual ~ECCompositor() {}
        virtual void Compose(ECParagraph * _paragraph) = 0;
        virtual int getCols() {return _numCols;}

    
    private:
        int _numCols;

};


class ECLineBreakWhole : public ECCompositor {
    public:
        ECLineBreakWhole(int numCols) : ECCompositor(numCols) {}
        ~ECLineBreakWhole() {}
        //Need to seperate each string by white space and put into vector 
        //Fill the existing lines with words, the empty lines should be removed
        virtual void Compose(ECParagraph * _paragraph);

        string findLastWord(string line);
        string findFirstWord(string line);
};


#endif