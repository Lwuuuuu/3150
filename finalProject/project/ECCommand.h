#ifndef ECCommand_h
#define ECCommand_h

#include <vector>
#include <iostream>
#include <stack>
#include "ECProj.h"
#include "ECChain.h"
using namespace std;

class ECProj;


class ECCommand
{
    public:
        ECCommand(int x, int y,ECProj * proj,int keyPressed) : x(x), y(y), pressedKey(keyPressed), proj(proj) {}
        virtual ~ECCommand() {}
        virtual void Execute() = 0;
        virtual void UnExecute() = 0;
        int getX() {return x;}
        int getY() {return y;}
        void setX(int new_x) {x = new_x;}
        void setY(int new_y) {y = new_y;}
        int getKey() {return pressedKey;}
        ECProj * getProj() {return proj;}
    private:
        ECProj * proj;
        int x;
        int y;
        int pressedKey;
};

class InsertTextCommand : public ECCommand {
    public:
        InsertTextCommand(int x, int y, int keyPressed, ECProj * proj) : ECCommand(x, y, proj, keyPressed) {}
        virtual void Execute();
        virtual void UnExecute();
};
class RemoveTextCommand : public ECCommand {
    public:
        RemoveTextCommand(int x, int y, int keyPressed, ECProj * proj, int flag) : ECCommand(x, y, proj, keyPressed), flag(flag) {} 
        virtual void Execute();
        virtual void UnExecute();        
        int getFlag() {return flag;}
    private:
        int flag;
};
class EnterCommand : public ECCommand {
    public:
        EnterCommand(int x, int y, int keyPressed, ECProj * proj) : ECCommand(x, y, proj, keyPressed) {}
        virtual void Execute();
        virtual void UnExecute();        
};
class DeleteCommand : public ECCommand {
    public:
        DeleteCommand(int x, int y, int keyPressed, ECProj * proj) : ECCommand(x, y, proj, keyPressed) {}
        virtual void Execute();
        virtual void UnExecute();        
};



// ******************************************************
// Implement command history

class ECCommandHistory 
{
public:
    ECCommandHistory() ;
    virtual ~ECCommandHistory();
    void ExecuteCmd(ECCommand * pCmd, int flag);
    void Redo();
    void Undo();
    stack<ECCommand *> getUndo() {return UndoHistory;}
    
private:
    stack<ECCommand *> UndoHistory; 
    stack<ECCommand *> RedoHistory; 

};


#endif /* ECCommand_h */
