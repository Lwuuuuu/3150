#include "ECComp.h"
using namespace std;

ECComponent::~ECComponent() {
    for (auto x : children) 
        delete x;
}


int ECComponent::getPos(ECComponent * obj) {
    int res = 0;
    for (auto x : children) {
        if (x == obj)
            break;
        else
            res++;
    }
    return res;
}

ECComposition::~ECComposition() {
    delete _compositor;
}

ECComposition::ECComposition(int numRows) {
    _compositor = new ECLineBreakWhole(numRows);
    _numRows = numRows;
}

int ECComposition::RemoveText(int x, int y, int keyPressed) {
    pair<int, ECParagraph *> paragraph = findParagraph(y);
    int paragraphPos = getPos(dynamic_cast<ECComponent *>(paragraph.second));      
    //Handles if backspace was pressed on the top of the paragraph and X = 0. Cannot be the first paragraph. Must merge the current paragraph with the previous paragraph
    if (x == 0 && paragraphPos > 0 && paragraph.first == 0) {

        for (auto x : paragraph.second->getChildren()) { 
            children[paragraphPos-1]->addChild(new ECRow(dynamic_cast<ECRow *>(x)->getLine()), children[paragraphPos-1]->getSize());            
        }    
        removeChild(paragraphPos);
        _compositor->Compose(dynamic_cast<ECParagraph *>(children[paragraphPos-1]));        
        return -1;
    }
    //Backspace press at x = 0 and you are not on the first line of the paragraph, delete last character of the previous line 
    else if (x == 0 && paragraph.first > 0) {
        int prevLength = dynamic_cast<ECRow *>(paragraph.second->getChildren()[paragraph.first-1])->getLine().length();
        int keyDeleted = paragraph.second->RemoveText(prevLength, paragraph.first-1, keyPressed);
        _compositor->Compose(dynamic_cast<ECParagraph *>(children[paragraphPos]));         
        return keyDeleted;
    }

    //If backspace was pressed in the middle of the paragraph. 
    else if (x != 0) {
        int keyDeleted = paragraph.second->RemoveText(x, paragraph.first, keyPressed);
        _compositor->Compose(dynamic_cast<ECParagraph *>(children[paragraphPos]));         
        return keyDeleted;
    }
    return -1;
}
void ECComposition::Enter(int x, int y, int keyPressed) {
    pair<int,ECParagraph *> paragraph = findParagraph(y);
    int paragraphPos = getPos(dynamic_cast<ECComponent *>(paragraph.second));   
    ECParagraph * newParagraph = new ECParagraph();
    //Beginning of line, not necessary for the test cases.
    if (x == 0) {
        newParagraph->addChild(new ECRow(""), 0);    
        addChild(newParagraph, paragraphPos);
    }
    //End of line
    else if (x ==  dynamic_cast<ECRow *>(paragraph.second->getChildren()[paragraph.first])->getLine().length()) {
        newParagraph->addChild(new ECRow(""), 0);
        addChild(newParagraph, paragraphPos+1);
        paragraph.second->Enter(x, paragraph.first, keyPressed);        
    }  
    else { //Middle of the line, have to interact with other paragraph do here  
        int paragraphPos = getPos(dynamic_cast<ECComponent *>(paragraph.second));    
        string line = dynamic_cast<ECRow *>(paragraph.second->getChildren()[paragraph.first])->getLine();
        string restofLine = string(line.begin()+x, line.end());
        //Rest of the line for the current line 
        newParagraph->addChild(new ECRow(restofLine), newParagraph->getSize());
        paragraph.second->Enter(x, paragraph.first, keyPressed);     
        int sz = paragraph.second->getSize();     
        for (int i = paragraph.first+1; i < sz; ++i) {
            newParagraph->addChild(new ECRow(dynamic_cast<ECRow *>(paragraph.second->getChildren()[i])->getLine()), newParagraph->getSize());
        }      
        for (int i = paragraph.first+1; i < sz; ++i) {
            paragraph.second->removeChild(paragraph.first+1);
        }           
        addChild(newParagraph, paragraphPos+1);
        _compositor->Compose(dynamic_cast<ECParagraph *>(children[paragraphPos+1]));         
    }


}
void ECComposition::InsertText(int x, int y, int keyPressed) {
    pair<int, ECParagraph *> paragraph = findParagraph(y);
    int paragraphPos = getPos(dynamic_cast<ECComponent *>(paragraph.second));    
    paragraph.second->InsertText(x, paragraph.first, keyPressed);
    _compositor->Compose(dynamic_cast<ECParagraph *>(children[paragraphPos]));  
}

int ECComposition::DeleteText(int x, int y, int keyPressed) {
    //Only case that will be passed in here is if a line still has characters in it, other cases delegated to backspace
    pair<int, ECParagraph *> paragraph = findParagraph(y);
    int paragraphPos = getPos(dynamic_cast<ECComponent *>(paragraph.second));    
    int keyDeleted = paragraph.second->DeleteText(x, paragraph.first, keyPressed);
    _compositor->Compose(dynamic_cast<ECParagraph *>(children[paragraphPos]));    
    return keyDeleted;
}

pair<int, ECParagraph *> ECComposition::findParagraph(int y) {
    int i = 0; 
    for (auto e : children) {   
        if (y - e->getSize() < 0) {
            if (y == 0) {
                return make_pair(0, dynamic_cast<ECParagraph *>(e));
            }
            else if ((y == e->getSize() && i != 0)) {
                return make_pair(e->getSize()-1, dynamic_cast<ECParagraph *>(children[i-1]));
            }              
            else {
                return make_pair(y, dynamic_cast<ECParagraph *>(e));
            }
        }
		else {
            y -= e->getSize();
            i++;
        }
	}
}

int ECComposition::numLines() {
    int sum = 0;
    for (auto x : children)
        sum += x->getSize();
    return sum;
}

int ECParagraph::RemoveText(int x, int y, int keyPressed) {
    if (x == 0) {
        return children[y-1]->RemoveText(dynamic_cast<ECRow *>(children[y-1])->getLine().length(), y, keyPressed);        
    }
    else {
        return children[y]->RemoveText(x, y, keyPressed);
    }
}
void ECParagraph::Enter(int x, int y, int keyPressed) {
    children[y]->Enter(x, y, keyPressed);
}
void ECParagraph::InsertText(int x, int y, int keyPressed) {
    children[y]->InsertText(x, y, keyPressed);
}

int ECParagraph::DeleteText(int x, int y, int keyPressed) {
    return children[y]->DeleteText(x, y, keyPressed);
}


int ECRow::RemoveText(int x, int y, int keyPressed) {
    int keyDeleted = static_cast<int>(_lineData[x-1]);
    _lineData = string(_lineData.begin(), _lineData.begin()+x-1) + 
    string(_lineData.begin()+x, _lineData.end());
    return keyDeleted;

}
void ECRow::Enter(int x, int y, int keyPressed) {
    _lineData = string(_lineData.begin(), _lineData.begin()+x);
}
void ECRow::InsertText(int x, int y, int keyPressed) {
    _lineData = string(_lineData.begin(), _lineData.begin()+x) + static_cast<char>(keyPressed) + string(_lineData.begin()+x, _lineData.end());
}

int ECRow::DeleteText(int x, int y, int keyPressed) {
    int keyDeleted = static_cast<int>(_lineData[x]);
    _lineData = string(_lineData.begin(), _lineData.begin()+x) + string(_lineData.begin()+x+1, _lineData.end());
    return keyDeleted;
}
