#include "ECChain.h"
#include <cstdlib>
#include <iostream>
using namespace std;


bool leftKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == ARROW_LEFT) {
        int lineNum = (projCtrl->curPage > 0) ? projCtrl->curPage * projCtrl->getRows() + y + 1 : projCtrl->curPage * projCtrl->getRows() + y;            
        if (x != 0) {
            projCtrl->getView()->SetCursorX(x-1);  
        }
        //If at first position and y = 0, but not first page
        else if (x == 0 && y == 0 && projCtrl->curPage > 0) {
            pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum - 1);   
            projCtrl->curPage--;
            int lastLine = projCtrl->curPage > 0 ? projCtrl->getRows() - 1 : projCtrl->getRows();
            projCtrl->getView()->SetCursorY(lastLine);
            projCtrl->getView()->SetCursorX(dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine().length());            
        }
        //X = 0 but not switching pages
        else if (x == 0 && projCtrl->getRows() * projCtrl->curPage + y > 0) {
            pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum - 1);   
            projCtrl->getView()->SetCursorY(y-1);
            projCtrl->getView()->SetCursorX(dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine().length());
        }
        return true;
    }
    else {
        insertKey next = insertKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}

bool rightKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == ARROW_RIGHT) {
        int lineNum = (projCtrl->curPage > 0) ? projCtrl->curPage * projCtrl->getRows() + y + 1 : projCtrl->curPage * projCtrl->getRows() + y;            
        pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum);
        int lineLength = dynamic_cast<ECRow *>(dynamic_cast<ECRow *>(line.second->getChildren()[line.first]))->getLine().length();
        int lastLine = projCtrl->curPage > 0 ? projCtrl->getRows() - 1 : projCtrl->getRows();

        //If not at end of the line
        if (x < lineLength) {
            projCtrl->getView()->SetCursorX(x+1);            
        }
        //At end of line at the end of the page
        else if (x == lineLength && y == lastLine) {
            projCtrl->getView()->SetCursorX(0);
            projCtrl->curPage++;
            projCtrl->getView()->SetCursorY(0);
        }
        //For when you are at the end of the line
        else if (projCtrl->getRows() * projCtrl->curPage + y < projCtrl->getComp()->numLines() - 1 && x == lineLength) {
            projCtrl->getView()->SetCursorX(0);
            projCtrl->getView()->SetCursorY(y + 1);
        }        
        return true;
    }
    else {
        leftKey next = leftKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}
bool downKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == ARROW_DOWN) {
        int numRows = projCtrl->getRows();
        int lineNum = (projCtrl->curPage > 0) ? projCtrl->curPage * projCtrl->getRows() + y + 1 : projCtrl->curPage * projCtrl->getRows() + y;            
        //Moving down to the next page, also check if at the very last line of last page
        int lastLine = projCtrl->curPage > 0 ? projCtrl->getRows() - 1 : projCtrl->getRows();
        if (y == lastLine && lineNum < projCtrl->getComp()->numLines() - 1) { 
            pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum + 1);   
            int bottomLine = dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine().length();
            if (x > bottomLine) 
                projCtrl->getView()->SetCursorX(bottomLine); 
            projCtrl->curPage++;
            projCtrl->getView()->SetCursorY(0);
                
        }
        //Moving down while staying on the same page
        else if (lineNum < projCtrl->getComp()->numLines() - 1 && y != numRows) {
            projCtrl->getView()->SetCursorY(y+1);
            pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum + 1);   
            int bottomLine = dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine().length();
            if (x > bottomLine) 
                projCtrl->getView()->SetCursorX(bottomLine);            
        }
        return true;   
    }
    else {
        rightKey next = rightKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}

bool upKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == ARROW_UP) {
        //First handle the case when you are at the top of the page and not on first page
        int lineNum = (projCtrl->curPage > 0) ? projCtrl->curPage * projCtrl->getRows() + y + 1 : projCtrl->curPage * projCtrl->getRows() + y;            
        if (y == 0 && projCtrl->curPage > 0) {
            projCtrl->curPage--;
            int lastLine = projCtrl->curPage > 0 ? projCtrl->getRows() - 1 : projCtrl->getRows();
            projCtrl->getView()->SetCursorY(lastLine);
            pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum - 1);   
            int topLine = dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine().length(); 
            if (x > topLine) 
                projCtrl->getView()->SetCursorX(topLine);             
        }
        //Handle case where you are in the middle of the page
        else if (y > 0) {
            projCtrl->getView()->SetCursorY(y-1);
            pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum - 1);   
            int topLine = dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine().length(); 
            if (x > topLine) 
                projCtrl->getView()->SetCursorX(topLine);             
        }

        return true;
    }
    else {
        downKey next = downKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}

bool homeKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == HOME_KEY) {
        projCtrl->getView()->SetCursorX(0);
        return true;
    }
    else {
        upKey next = upKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}

bool endKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == END_KEY) {
        int lineNum = (projCtrl->curPage > 0) ? projCtrl->curPage * projCtrl->getRows() + y + 1 : projCtrl->curPage * projCtrl->getRows() + y;   
        pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum);         
        int lineLength = dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine().length();                    
        projCtrl->getView()->SetCursorX(lineLength);
        return true;
    }
    else {
        homeKey next = homeKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }

}

bool redoKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == CTRL_Y) {
        projCtrl->getHist()->Redo();
        return true;
    }
    else {
        endKey next = endKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}
bool undoKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == CTRL_Z) {
        projCtrl->getHist()->Undo();
        return true;
    }
    else {
        redoKey next = redoKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}

bool enterKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed  == ENTER || flag == 1) {
        int lineNum;
        if (flag == 1)
            lineNum = y;
        else
            lineNum = (projCtrl->curPage > 0) ? projCtrl->curPage * projCtrl->getRows() + y + 1 : projCtrl->curPage * projCtrl->getRows() + y;   
        projCtrl->getComp()->Enter(x, lineNum, keyPressed);
        //if not at the end of the page
        if (y != projCtrl->getRows()) {
            projCtrl->getView()->SetCursorX(0);
            projCtrl->getView()->SetCursorY(y+1);            
        }
        //At the end of the page
        int lastLine = projCtrl->curPage > 0 ? projCtrl->getRows() - 1 : projCtrl->getRows();
        if (y == lastLine) {
            projCtrl->curPage++;
            //At the end of the line
            projCtrl->getView()->SetCursorX(0);
            projCtrl->getView()->SetCursorY(0);
        }
        projCtrl->getHist()->ExecuteCmd(new EnterCommand(x, lineNum, -1, projCtrl), flag);
        return true;
    }
    else {
        undoKey next = undoKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}
bool deleteKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == DEL_KEY || flag == 1) {
        int lineNum;
        if (flag == 1)
            lineNum = y;
        else
            lineNum = (projCtrl->curPage > 0) ? projCtrl->curPage * projCtrl->getRows() + y + 1 : projCtrl->curPage * projCtrl->getRows() + y;            
        pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum);         
        int lineLength = dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine().length();
        if (x == lineLength) { //Pressing delete on the end of a line while there are more lines beneth it will bring the beneth line on to current line
            if (projCtrl->getComp()->numLines() - 1 > lineNum) { //Checks to see if there are lines under it (#of Rows)
                //Same as if you are pressing backspace when you are the 0th position 
                backspaceKey newObj = backspaceKey(projCtrl);
                bool success = newObj.Handle(0, y+1, BACKSPACE, flag);
            }
        }
        //Only job that has to be done on delete command, other cases handled by backspace
        else if (lineLength > 0) { //If a line still has characters in it
            //Deletes the character that the cursor is currently on
            int keyDeleted = projCtrl->getComp()->DeleteText(x, lineNum, keyPressed);                    
            projCtrl->getHist()->ExecuteCmd(new DeleteCommand(x, lineNum, keyDeleted, projCtrl), flag);
        }
        else if (lineNum == projCtrl->getComp()->numLines() - 1) {} //If pressing delete on an empty line where there are no more lines after it, it remains empty. Do nothing.     
        else if (projCtrl->getComp()->numLines() > 1 && lineLength == 0) { //When pressing delete on an empty line that is not the top line, delete that line
            //Deleteing a line is the same as Backspacing/RemoveText when X-Cursor is at 0
            backspaceKey newObj = backspaceKey(projCtrl);
            bool success = newObj.Handle(0, y+1, BACKSPACE, flag);
        }    
        return true;        
    }   
    else {
        enterKey next = enterKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }  
}

bool backspaceKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == BACKSPACE) {
        pair<int, ECParagraph *> line;
        string topLine;
        int lineNum;       
        if (projCtrl->curPage * projCtrl->getRows() + y != 0 || x != 0) {
            if (flag == 1) {
                lineNum = y;                
            }
            else {
                lineNum = (projCtrl->curPage > 0) ? projCtrl->curPage * projCtrl->getRows() + y + 1 : projCtrl->curPage * projCtrl->getRows() + y;            
            }
            if  (y > 0) {
                line = projCtrl->getComp()->findParagraph(lineNum - 1);                           
                topLine = dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine();                 
            }
            pair<int, ECParagraph *> curLine = projCtrl->getComp()->findParagraph(lineNum);                           
            string curData = dynamic_cast<ECRow *>(curLine.second->getChildren()[curLine.first])->getLine();         
            //When at beginning position of line and at top of page
            if (x == 0 && y == 0 && projCtrl->curPage > 0) {            
                projCtrl->curPage--;
                if (isspace(topLine.back())) {
                    projCtrl->getView()->SetCursorX(topLine.length() - 1);
                }
                else {
                    projCtrl->getView()->SetCursorX(topLine.length());
                }                
                int lastLine = projCtrl->curPage > 0 ? projCtrl->getRows() - 1 : projCtrl->getRows();
                projCtrl->getView()->SetCursorY(lastLine);       
                int keyDeleted = projCtrl->getComp()->RemoveText(x, lineNum, keyPressed);
                projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX(), lastLine, -1, projCtrl, 1), flag);   
            }                
            //When at beginning position of the line but not at the top of the page
            else if (x == 0 && lineNum > 0) {              
                if (curData.length() == 0) {
                    projCtrl->getView()->SetCursorX(topLine.length());
                    projCtrl->getView()->SetCursorY(y - 1);         
                    int keyDeleted = projCtrl->getComp()->RemoveText(x, lineNum, keyPressed);
                    projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX(), lineNum - 1, keyDeleted, projCtrl, 1), flag);                                  
                }
                //Going to delete that space, which will merge the two words together                
                else if (isspace(topLine.back()) && curLine.first > 0) {
                    string lastWord = projCtrl->getComp()->getCompositor().findLastWord(topLine);                 
                    string firstWord = projCtrl->getComp()->getCompositor().findFirstWord(curData);
                    //If it will fit, go to the previous line 
                    if (topLine.length() - 1 + firstWord.length() <= projCtrl->getView()->GetColNumInView() - 1) {
                        projCtrl->getView()->SetCursorX(topLine.length() - 1);
                        projCtrl->getView()->SetCursorY(y - 1);                           
                        int keyDeleted = projCtrl->getComp()->RemoveText(x, lineNum, keyPressed);
                        projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX(), lineNum - 1, keyDeleted, projCtrl, 1), flag);                        
                    }
                    else {
                        //Doesnt fit and the last word of the previous line will go to the current line
                        projCtrl->getView()->SetCursorX(lastWord.length() - 1);
                        projCtrl->getView()->SetCursorY(y);                    
                        int keyDeleted = projCtrl->getComp()->RemoveText(x, lineNum, keyPressed);
                        projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX() + 1, lineNum, keyDeleted, projCtrl, 1), flag);                     
                    }
                }
                //Delete the last character of the previous line
                else {
                    projCtrl->getView()->SetCursorX(topLine.length());
                    projCtrl->getView()->SetCursorY(y - 1);
                    int keyDeleted = projCtrl->getComp()->RemoveText(x, lineNum, keyPressed);
                    //If merging the current paragraph with the previous paragraph 
                    if (curLine.first == 0) {
                        projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX(), lineNum - 1, keyDeleted, projCtrl, 0), flag);                     
                    }
                    //Deleting the last character of the previous line. May not run as all words end with a space unless last word of a paragraph, then above will run 
                    else {
                        projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX() + 1, lineNum - 1, keyDeleted, projCtrl, 1), flag);                     
                    }
                }
           
            }
            //When in the middle of the page and anywhere in the line
            else if (x != 0) {                                                     
                string firstWord = projCtrl->getComp()->getCompositor().findFirstWord(curData);
                int keyDeleted;
                //If pressing backspace when cursor at end of line and end of line is a space will merge last word of the current line with first word of the next line            
                if (x == curData.length() && isspace(curData.back()) && curLine.first < curLine.second->getSize() - 1) {  
                    pair<int, ECParagraph *> bottomLine = projCtrl->getComp()->findParagraph(lineNum + 1);                           
                    string bottomData = dynamic_cast<ECRow *>(bottomLine.second->getChildren()[bottomLine.first])->getLine();          
                    string bottomFirstWord = projCtrl->getComp()->getCompositor().findFirstWord(bottomData);
                    //Combination of last word of current line and first word of bottom line  can't fit on current line, bring down to next line
                    if (bottomFirstWord.length() + curData.length() - 1 > projCtrl->getView()->GetColNumInView() - 1) {
                        string lastWord = projCtrl->getComp()->getCompositor().findLastWord(curData);
                        projCtrl->getView()->SetCursorX(lastWord.length() - 1);
                        projCtrl->getView()->SetCursorY(y + 1);                    
                        keyDeleted = projCtrl->getComp()->RemoveText(x, lineNum, keyPressed);
                        projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX() + 1, lineNum + 1, keyDeleted, projCtrl, 1), flag);
                    }
                    else {
                        projCtrl->getView()->SetCursorX(x - 1);
                        keyDeleted = projCtrl->getComp()->RemoveText(x, lineNum, keyPressed);
                        projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX(), lineNum, keyDeleted, projCtrl, 1), flag);
                    }
                }
                //If pressing backspace will cause the first word of the current line to move to the end of the top line
                else {
                    keyDeleted = projCtrl->getComp()->RemoveText(x, lineNum, keyPressed);
                    //Not space because since we delete the space we are combining the first word with the things after it
                    if (firstWord.length() + topLine.length() - 1 <= projCtrl->getView()->GetColNumInView() - 1 && x <= firstWord.length() && curLine.first > 0 && (x == curData.length() && keyDeleted == 32 || keyDeleted != 32)) {
                        projCtrl->getView()->SetCursorX(projCtrl->getView()->GetColNumInView() - 1 - firstWord.length() + x);
                        //Might have to move to previous page
                        if (x == firstWord.length() && y == 0 && projCtrl->curPage > 0) {
                            int lastLine = projCtrl->curPage > 0 ? projCtrl->getRows() - 1 : projCtrl->getRows();
                            projCtrl->getView()->SetCursorY(lastLine); 
                            projCtrl->curPage--;
                            projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX() + 1, lastLine, keyDeleted, projCtrl, 1), flag);

                        }
                        else { 
                            projCtrl->getView()->SetCursorY(y - 1);
                            projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(projCtrl->getView()->GetCursorX() + 1, lineNum - 1, keyDeleted, projCtrl, 1), flag);

                        }
                    }
                    else {
                        projCtrl->getView()->SetCursorX(x-1);
                        projCtrl->getView()->SetCursorY(y);
                        projCtrl->getHist()->ExecuteCmd(new RemoveTextCommand(x, lineNum, keyDeleted, projCtrl, 1), flag);
                    }
                }
            }
        }
        return true;
    }
    else {
        
        deleteKey next = deleteKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}

bool quitKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed == CTRL_Q) {      
        ofstream outfile;
        string line;
        outfile.open(projCtrl->_fileName);
        for (auto x : projCtrl->getComp()->getChildren()) {
            for (auto e : x->getChildren()) {
                line += dynamic_cast<ECRow *>(e)->getLine();                
            }
            outfile << line +'\n';
            line.clear();
        }
        projCtrl->getView()->Quit();      
        // static const char *command = string("clear").c_str();
        // std::system(command);             
        return true;
    }
    else {
        backspaceKey next = backspaceKey(projCtrl);
        return next.Handle(x, y, keyPressed, flag);
    }
}

bool insertKey::Handle(int x, int y, int keyPressed, int flag) {
    if (keyPressed > 31 && keyPressed < 128) {
        int lineNum;
        // pair<int, ECParagraph *> line;
        string curLine;        
        //Need to reupdate the y values passed in from Undo because the X and Y values could of changed because of link breaking
        if (flag == 1) {
            lineNum = y;
        }
        else {
            lineNum = (projCtrl->curPage > 0) ? projCtrl->curPage * projCtrl->getRows() + y + 1 : projCtrl->curPage * projCtrl->getRows() + y;
          
        }
        pair<int, ECParagraph *> line = projCtrl->getComp()->findParagraph(lineNum);    
        curLine = dynamic_cast<ECRow *>(line.second->getChildren()[line.first])->getLine();  
        int lastSpace;
        string lastWord;
        int i = 0;
        bool seenSpace = false;
        for (auto character : curLine) {
            lastWord += character;
            if (isspace(character)) {
                seenSpace = true; 
            }
            //New word occurence
            else if (!isspace(character) && seenSpace == true) {
                lastSpace = i - 1;
                lastWord.clear();
                lastWord += character;
                seenSpace = false;
            }
            i++;
        }         
        //If Cursor is at the end of the view or the Cursor is part of the last word and the line will be larger than the view
        if (x == projCtrl->getView()->GetColNumInView() - 1 || (x > lastSpace && curLine.length() >= projCtrl->getView()->GetColNumInView() - 1)) {
            //Cursor at end of the view and the last character of the line is a space, then move over to next line. Do not carry over the last word. Put the pressed key at x = 0
            if (x  == projCtrl->getView()->GetColNumInView() - 1 && isspace(curLine.back())) {
                projCtrl->getView()->SetCursorX(1);
                projCtrl->getHist()->ExecuteCmd(new InsertTextCommand(0, lineNum + 1, keyPressed, projCtrl), flag);                    
            }            
            //X cursor was at the end of the line and no space, meaning the lastword will carry over to the next line             
            else if (x == projCtrl->getView()->GetColNumInView()- 1) {            
                projCtrl->getView()->SetCursorX(lastWord.length() + 1);
                projCtrl->getHist()->ExecuteCmd(new InsertTextCommand(lastWord.length(), lineNum + 1, keyPressed, projCtrl), flag);    
            }

            //the character at the X cursor position was part of the last word of the line, but not at the end of the view and the current lines length is at end of view
            else {
                //Space was pressed and X was not at the end of view and X was not at the end of the last word. 
                //Will take the case where you press space in the middle of the word. Will put the second half of the word on the first line
                if (keyPressed == 32 && x != projCtrl->getView()->GetColNumInView() - 1 && x != lastSpace + lastWord.length()) {
                    projCtrl->getView()->SetCursorX(0);
                    projCtrl->getHist()->ExecuteCmd(new InsertTextCommand(0, lineNum + 1, keyPressed, projCtrl), flag);    
                }
                //The entire word is carried over
                else {
                    projCtrl->getView()->SetCursorX(x - lastSpace);
                    projCtrl->getHist()->ExecuteCmd(new InsertTextCommand(x - lastSpace - 1, lineNum + 1, keyPressed, projCtrl), flag);    
                }
            }

            int lastLine = projCtrl->curPage > 0 ? projCtrl->getRows() - 1 : projCtrl->getRows();
            if (y == lastLine) {
                projCtrl->getView()->SetCursorY(0);
                projCtrl->curPage++;
            }
            else {
                projCtrl->getView()->SetCursorY(y+1); 
            }       
            projCtrl->getComp()->InsertText(x, lineNum, keyPressed);    
        }
        else {    
            pair<int, ECParagraph *> current = projCtrl->getComp()->findParagraph(lineNum);                          
            string currentLine = dynamic_cast<ECRow *>(current.second->getChildren()[current.first])->getLine();    
            //If space was pressed and not first row of the paragraph and the top line can fit the characters before and including the X cursor, then first half of word moves to top line 
            if (keyPressed == 32 && current.first > 0) {
                pair<int, ECParagraph *> upper = projCtrl->getComp()->findParagraph(lineNum - 1);  
                string topLine = dynamic_cast<ECRow *>(upper.second->getChildren()[upper.first])->getLine();                
                //If the topLine can fit what the first half of the word before and including X 
                if (x + topLine.length() < projCtrl->getView()->GetColNumInView() - 1) {
                    projCtrl->getView()->SetCursorX(0);
                    projCtrl->getView()->SetCursorY(y);    
                    projCtrl->getComp()->InsertText(x, lineNum, keyPressed);    
                    projCtrl->getHist()->ExecuteCmd(new InsertTextCommand(x + topLine.length(), lineNum - 1, keyPressed, projCtrl), flag); 
                    return true;
                }               
            }    
            //If the current line has spaces at the end of the line and can fit more just start appending to beginning of bottom
            if (keyPressed != 32 && x == currentLine.length() && current.second->getSize() > 1 && current.first < current.second->getSize() - 1) {
                projCtrl->getView()->SetCursorX(1);
                projCtrl->getView()->SetCursorY(y+1);    
                projCtrl->getComp()->InsertText(x, lineNum, keyPressed);    
                projCtrl->getHist()->ExecuteCmd(new InsertTextCommand(0, lineNum + 1, keyPressed, projCtrl), flag); 
            }
            // Default
            else {
                projCtrl->getView()->SetCursorX(x+1);
                projCtrl->getView()->SetCursorY(y);    
                projCtrl->getComp()->InsertText(x, lineNum, keyPressed);    
                projCtrl->getHist()->ExecuteCmd(new InsertTextCommand(x, lineNum, keyPressed, projCtrl), flag);            
            }

        }
    }
    return true;
}

