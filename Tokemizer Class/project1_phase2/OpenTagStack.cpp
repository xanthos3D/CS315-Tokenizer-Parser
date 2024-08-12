//
// Created by xmani on 2/2/2023.
//
//
// Created by Ali Kooshesh on 1/22/23.
//

#include "OpenTagStack.hpp"
#include <iostream>

void OpenTagStack::addTag(const Token& token) {
    stack.push_back(token);
}
bool OpenTagStack::empty() {  // is the stack empty?
    if (stack.size() == 0) {
        return true;
    }
    return false;
}
// i think i need this to determing if a proper closing tag that does not match the current
//open tag on the opentag stack or it is a random closing tag that that connects to a open tag somewhere deeper in the stack.
//function traverses stack and return true if it finds a matching tag deeper in the stack or false if it cant find a matching tag
bool OpenTagStack::findTagInStack(std::string tagName) {
    //traverse the stack in reverse to determine if a open tag matches the give close tag.
    for (int index = stack.size() - 1; index > 0; index--) {
        if (stack.at(index).tagName() == tagName) {
            return true;
        }

    }
    return false;
}

Token OpenTagStack::top() { // returns the top element.
    // top writes an error message and terminates the application if stack is empty.
    //returns the token at the end of the vector acting as a stack
    return stack[stack.size()-1];
}
void OpenTagStack::pop() {  // removes the top element from the stack.
    // pop writes an error message and terminates the application if the stack is empty.
    // removeElementWithTagName searches the stack from top to bottom and
    // if there is a token whose tag-name matches tagName, that element
    // gets removed from the stack. If the element doesn't exist, this function
    // doesn't make any changes to the stack.
    stack.pop_back();
}
void OpenTagStack::removeElementWithTagName(std::string tagName) {
    //for loop that loops through the vector and if the tag name matches the tag passed here then remove that token.
    // we need to traverse through the loop backwards so the nearest tag that matches the current close tag can be found and removed from the stack
    // and added to the complete tags stack.
    bool elementFound = false;
    for (int index = stack.size()-1; index > 0;index--) {
        if (stack.at(index).tagName() == tagName && elementFound == false) {
            elementFound = true;
            // errases the element found.
            stack.erase(stack.begin()+index);
        }

    }

}
void OpenTagStack::printStack() {
    // Use this function as a debugging tool to print all tokens that
    // are currently on the stack.
    std::cout <<"Printing Stack" << std::endl;
    for (int index = 0; index < stack.size(); index++) {
        stack.at(index).print();
        std::cout << ", ";

    }
    std::cout << std::endl;

}

// printTokensAbove is used when the token that is ot the top of the stack
// does not match the currently identified token from the input.
// Here is the potential use for this function (text from sampleInput2_output.txt
// [13, 524] </tr closes while the following tags remain open.
// [13, 483] <em
// [13, 471] <p
// In this example, parser has found the close-tag </tr. However, that doesn't match the element
// that is on top of the stack (<em is on top of the stack). As a result, this function
// gets called with argument "tr". It prints the two tokens that sit above <tr (<tr has not
// been shown here.
// [13, 483] <em
// [13, 471] <p
// Then, you would call removeElementWithTagName and pass "tr" to it to remove the open-tag "tr".
void OpenTagStack::printTokensAbove(std::string tagName) {

    int tagPlacement = -1;
    //loop to find the tag placement
    for (int index = stack.size()-1; index > 0; index-- ) {
        //if we find the tag we are looking for we spit it out with the error message
        if (stack.at(index).tagName() == tagName && tagPlacement == -1 ) {
            //sets the location of the tag so that tags after it can be printed.
            tagPlacement = index;

        }
    }
    // loop to properly print the tags after it
    for (int index = stack.size()-1; index > 0; index--) {
        if (tagPlacement < index) {// otherwise we print the tokens after it.
            std::cout << "       ";
            stack.at(index).print();
            std::cout << std::endl;
        }

    }


}
