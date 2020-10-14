#include "ECCommand.h"


// ******************************************************
// Implement command history

ECCommandHistory :: ECCommandHistory() {}

ECCommandHistory :: ~ECCommandHistory() {
    while(!RedoHistory.empty()) {
        ECCommand * top = RedoHistory.top();
        delete top;
        RedoHistory.pop();
    }
    while(!UndoHistory.empty()) {
        ECCommand * top = UndoHistory.top();
        delete top;    
        UndoHistory.pop();
    }
}

void ECCommandHistory::Undo() {
    if (!UndoHistory.empty()) {
        ECCommand * top = UndoHistory.top();
        UndoHistory.pop();
        RedoHistory.push(top);
        top->UnExecute();
    }
}
void ECCommandHistory::Redo() {
    if (!RedoHistory.empty()) {
        ECCommand * top = RedoHistory.top();
        RedoHistory.pop();
        UndoHistory.push(top);
        top->Execute();
    }
}

void ECCommandHistory::ExecuteCmd(ECCommand * pCmd, int flag) {
  if (flag == 0) {
    UndoHistory.push(pCmd);       
    while(!RedoHistory.empty()) {  
        ECCommand * top = RedoHistory.top();
        delete top;          
        RedoHistory.pop();
    }
  }
  else {
      delete pCmd;
  }
}

// ******************************************************
// ECCommand Derived Class Methods


void InsertTextCommand::Execute() {
    insertKey newObj = insertKey(getProj());
    newObj.Handle(getX(), getY(), getKey(), 1);
}
void InsertTextCommand::UnExecute() {
    backspaceKey newObj = backspaceKey(getProj());
    newObj.Handle(getX()+1, getY(), BACKSPACE, 1);
}
void RemoveTextCommand::Execute() {
    if (getFlag() == 1) { //Normal backspace
        if (getKey() == 32) {
            backspaceKey newObj = backspaceKey(getProj());
            newObj.Handle(0, getY(), BACKSPACE, 1);
        }
        else {
            backspaceKey newObj = backspaceKey(getProj());
            newObj.Handle(getX(), getY(), BACKSPACE, 1);
        }
    }
    else { //Hitting backspace at x = 0, y = Y
        deleteKey newObj = deleteKey(getProj());
        newObj.Handle(getX(), getY(), DEL_KEY, 1);
    }
}
void RemoveTextCommand::UnExecute() {
    if (getFlag() == 1) { //Normal backspace, decrement X val because backspace removes character before cursor, while Insert adds on the cursor position
        insertKey newObj = insertKey(getProj());
        newObj.Handle(getX() - 1, getY(), getKey(), 1);
    }
    else { //Means you hit backspace at cursor point 0
        enterKey newObj = enterKey(getProj());
        newObj.Handle(getX(), getY(), ENTER, 1);
    }
}
void EnterCommand::Execute() {
    enterKey newObj = enterKey(getProj());
    newObj.Handle(getX(), getY(), ENTER, 1);
}
void EnterCommand::UnExecute() {
    //X and Y are the cursor positions whre you pressed enter. If you press delete at this point it will merge the line the cursor is on and the below line
    deleteKey newObj = deleteKey(getProj());
    newObj.Handle(getX(), getY(), DEL_KEY, 1);
}
void DeleteCommand::Execute() {
    deleteKey newObj = deleteKey(getProj());
    newObj.Handle(getX(), getY(), DEL_KEY, 1);
}
void DeleteCommand::UnExecute() {
    insertKey newObj = insertKey(getProj());
    newObj.Handle(getX(), getY(), getKey(), 1);
    //Insert text will increment the cursor X pos, When you undo delete the cursor position is maintained. 
    getProj()->getView()->SetCursorX(getProj()->getView()->GetCursorX()-1);
}


