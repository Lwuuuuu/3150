#ifndef ECComp_h
#define ECComp_h
#include "ECTextViewImp.h"
#include "ECCompose.h"
#include <vector>
#include <string>
#include <utility>
using namespace std;

class ECCompositor;
class ECLineBreakWhole;
class ECProj;
class ECComponent {
    public: 
        virtual ~ECComponent();
        ECComponent() {} 
        virtual void addChild(ECComponent * child, int pos) {children.insert(children.begin()+pos, child);};
        virtual void removeChild(int pos) {children.erase(children.begin()+pos);}
        vector<ECComponent *> & getChildren() {return children;}
        void clearChildren() {children.clear();}
        int getSize() {return children.size();}
        int getPos(ECComponent * obj);
        virtual void InsertText(int x, int y, int keyPressed) = 0;
        virtual int RemoveText(int x, int y, int keyPressed) = 0;
        virtual void Enter(int x, int y, int keyPressed) = 0;  
        virtual int DeleteText(int x, int y, int keyPressed) = 0;

        vector<ECComponent *> children;
};


class ECParagraph : public ECComponent {
    public:
        ECParagraph() {}
        ~ECParagraph() {}
        virtual int RemoveText(int x, int y, int keyPressed);
        virtual void Enter(int x, int y, int keyPressed);
        virtual void InsertText(int x, int y, int keyPressed);
        virtual int DeleteText(int x, int y, int keyPressed);
};

class ECRow : public ECComponent {
    public: 
        ECRow(string _initData) : _lineData(_initData) {}
        ~ECRow() {} 
        virtual int RemoveText(int x, int y, int keyPressed);
        virtual void Enter(int x, int y,int keyPressed);
        virtual void InsertText(int x, int y, int keyPressed);
        virtual int DeleteText(int x, int y, int keyPressed);        
        string getLine() {return _lineData;}
        void prependString(string line) {_lineData = line + _lineData;}
        void appendString(string line) {_lineData += line;}        
        void deleteEnd(int pos) {_lineData = string(_lineData.begin(), _lineData.end()-pos);}
        void deleteBeginning(int pos) {_lineData = string(_lineData.begin()+pos, _lineData.end());}
    private: 
        string _lineData;
};


class ECComposition : public ECComponent {
    public: 
        ECComposition(int numRows);
        ~ECComposition();
        virtual int RemoveText(int x, int y, int keyPressed);
        virtual void Enter(int x, int y, int keyPressed);
        virtual void InsertText(int x, int y, int keyPressed);
        virtual int DeleteText(int x, int y, int keyPressed);
        pair<int, ECParagraph *> findParagraph(int y);
        int numLines();
        ECLineBreakWhole & getCompositor() {return *_compositor;}
    private:
        ECLineBreakWhole * _compositor; 
        int _numRows;
};
#endif