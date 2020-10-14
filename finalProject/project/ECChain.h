#ifndef ECChain_h
#define ECChain_h
#include "ECProj.h"
#include "ECCommand.h"
#include <utility>
#include <stack>
#include <fstream>
#include <queue> 
//******************************************
//Chain
//backspaceKey -> deleteKey -> enterKey -> undoKey -> redoKey -> endKey -> homeKey -> upKey -> downkey -> rightkey -> leftkey ->insertKey
class  ECProj;
class KeyEvtHandler {
    public:
        KeyEvtHandler(ECProj * proj) : projCtrl(proj) {}
        virtual ~KeyEvtHandler() {}
        virtual bool Handle(int x, int y, int keyPressed, int flag) = 0;
        ECProj * projCtrl;
};
class insertKey : public KeyEvtHandler {
    public:
        insertKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        
};
class leftKey : public KeyEvtHandler {
    public:
        leftKey(ECProj * proj) : KeyEvtHandler(proj)  {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        

};

class rightKey : public KeyEvtHandler {
    public:
        rightKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        

};

class downKey : public KeyEvtHandler {
    public:
        downKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        

};

class upKey : public KeyEvtHandler {
    public:
        upKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        

};

class homeKey : public KeyEvtHandler {
    public:
        homeKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        

};

class endKey : public KeyEvtHandler {
    public:
        endKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        

};


class backspaceKey : public KeyEvtHandler {
    public:
        backspaceKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);   
             

};

class enterKey : public KeyEvtHandler {
    public:
        enterKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        

};

class deleteKey : public KeyEvtHandler {
    public:
        deleteKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        

};
class redoKey : public KeyEvtHandler {
    public:
        redoKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        

};
class undoKey : public KeyEvtHandler {
    public:
        undoKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        
};

class quitKey : public KeyEvtHandler {
    public:
        quitKey(ECProj * proj) : KeyEvtHandler(proj) {}
        virtual bool Handle(int x, int y, int keyPressed, int flag);        
};


#endif