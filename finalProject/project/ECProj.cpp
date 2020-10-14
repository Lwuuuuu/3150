#include "ECProj.h"
ECProj::ECProj(std::string fileName) {
    _fileName = fileName;
    view = new ECTextViewImp();
    view->AddStatusRow("left", "right", true);
    rows = view->GetRowNumInView() - 2;
    histCmds = new ECCommandHistory();
    view->Attach(this);
    comp = new ECComposition(view->GetColNumInView());    
    addData(fileName);

}

ECProj::~ECProj() {
    view->Detach(this);
    delete view;
    delete histCmds;
    delete comp;
}

void ECProj::populateRows() {
    view->InitRows();
    view->AddRow("");
    vector<std::string> data;
    for (auto x : comp->getChildren()) {
        for (auto e : x->getChildren()) {
            data.push_back(dynamic_cast<ECRow *>(e)->getLine());
        }
    }
    int START = curPage > 0 ? curPage * rows + 1 : curPage * rows;
    int STOP = data.size() < (curPage + 1) * rows ? data.size() : (curPage + 1) * rows + 1;
    for (int i = START; i < STOP; ++i) {
        if (i <= data.size() - 1)
            view->AddRow(data[i]);
    }


    view->Refresh();
}

void ECProj::addData(std::string fileName) {
    std::ifstream ipt(fileName); 
    std::string line; 
    if (ipt.is_open()) {
        while (std::getline(ipt,line)) {
            ECParagraph * newParagraph = new ECParagraph();
            if (line.length() > 0) {
                if(!isalpha(line.back())) {
                    line.pop_back();
                }
            }
            newParagraph->addChild(new ECRow(line), 0);
            comp->addChild(newParagraph, comp->getSize());
        }
        ipt.close();
    }
    else {
        ECParagraph * newParagraph = new ECParagraph();
        newParagraph->addChild(new ECRow(""), 0);
        comp->addChild(newParagraph, comp->getSize());
    }
    for (auto x : comp->getChildren()) {
        comp->getCompositor().Compose(dynamic_cast<ECParagraph *>(x));            
        comp->getCompositor().Compose(dynamic_cast<ECParagraph *>(x));            
    }
    populateRows();
}

void ECProj::Update() {
    int keyPressed = view->GetPressedKey();
    int x = view->GetCursorX();
    int y = view->GetCursorY();
    quitKey newObj = quitKey(this);
    bool success = newObj.Handle(x, y, keyPressed, 0);
    if (success && keyPressed != CTRL_Q) {
        populateRows();
    }
}