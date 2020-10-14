#include "ECCompose.h"
#include <iostream>
#include <sstream>
using namespace std;

string ECLineBreakWhole::findLastWord(string line) {
    string word; 
    bool seenSpace = false;
    for (auto character : line) {
        word += character;
        if (isspace(character))
            seenSpace = true; 
        //New word occurence
        else if (!isspace(character) && seenSpace == true) {
            word.clear();
            word += character;
            seenSpace = false;
        }
    }
    return word;
}

string ECLineBreakWhole::findFirstWord(string line) {
    string word;
    bool seenSpace = false;
    for (auto character : line) {
        if (isspace(character))
            seenSpace = true; 
        //New word occurence
        else if (!isspace(character) && seenSpace == true) {
            return word;
        }
        word += character;
    }
    return word;
}


void ECLineBreakWhole::Compose(ECParagraph * _paragraph) {
    int i = 0; 
    while (i < _paragraph->getSize()) {
        string line = dynamic_cast<ECRow* >(_paragraph->getChildren()[i])->getLine();
        //Putting the beginning word of the next line on to the end of the current line if the current line does not end with a space. Cannot be last row
        if (!isspace(line.back()) && i != _paragraph->getSize() - 1) {
            string lowerLine = dynamic_cast<ECRow* >(_paragraph->getChildren()[i+1])->getLine();
            if (lowerLine.length() > 0) {
                string firstWord = findFirstWord(lowerLine);
                dynamic_cast<ECRow *>(_paragraph->getChildren()[i+1])->deleteBeginning(firstWord.length());
                dynamic_cast<ECRow *>(_paragraph->getChildren()[i])->appendString(firstWord);             
            }
            else {
                _paragraph->removeChild(i+1);
                i++;
            }
        }
        //For inserting text want to carry the text over to the new line
        else if (line.length() > getCols() - 1) {
            string lastWord = findLastWord(line);
            //Insert new line
            if (i == _paragraph->getSize() - 1) {
                dynamic_cast<ECRow *>(_paragraph->getChildren()[i])->deleteEnd(lastWord.length());                                           
                _paragraph->addChild(new ECRow(lastWord), i+1);                
            }
            //Prepend to next lines string
            else {
                dynamic_cast<ECRow *>(_paragraph->getChildren()[i])->deleteEnd(lastWord.length());
                dynamic_cast<ECRow *>(_paragraph->getChildren()[i+1])->prependString(lastWord);
                if (dynamic_cast<ECRow* >(_paragraph->getChildren()[i])->getLine().length() <= getCols()) {
                    i++;
                }                
            }          
        }
        //For backspacing have to append the first word of the next lien to the current line
        else if (line.length() < getCols()) {
            //Cannot be the first line in the paragraph
            if (i != _paragraph->getSize() - 1) {
                string nextLine = dynamic_cast<ECRow* >(_paragraph->getChildren()[i+1])->getLine();
                if (nextLine.length() == 0) {
                    _paragraph->removeChild(i+1);
                }
                else {
                    string firstWord = findFirstWord(nextLine);
                    if (firstWord.length() + line.length() <= getCols() - 1) {
                        dynamic_cast<ECRow *>(_paragraph->getChildren()[i+1])->deleteBeginning(firstWord.length());
                        dynamic_cast<ECRow *>(_paragraph->getChildren()[i])->appendString(firstWord);                    
                    }
                    else
                        i++;
                }
            }
            else 
                i++;
        }
        else {
            i++;
        }
    }
}

