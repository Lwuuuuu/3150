#ifndef ECPROJ_H
#define ECPROJ_H

#include "ECObserver.h"
#include "ECCommand.h"
#include "ECTextViewImp.h"
#include "ECComp.h"
#include <vector>
#include <string>
#include <fstream>
class ECTextViewImp;
class ECCommandHistory;
class ECComposition; 

class ECProj : public ECObserver {
    public:
        ECProj(std::string fileName);
        ~ECProj(); 
        void Update();
        ECTextViewImp * getView() {return view;}
        ECCommandHistory * getHist() {return histCmds;}
        ECComposition * getComp() {return comp;}   
        void populateRows();
        int curPage = 0;  
        int getRows() {return rows;}  
        std::string _fileName;
    private:
        void addData(std::string fileName);
        ECTextViewImp * view;
        ECCommandHistory * histCmds;
        ECComposition * comp;
        int rows;
        
};
#endif