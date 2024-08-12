//
// Created by xmani on 2/2/2023.
//
//
// Created by Ali Kooshesh on 1/22/23.
//

#ifndef PROJECT1_PHASE2_OPENTAGSTACK_HPP
#define PROJECT1_PHASE2_OPENTAGSTACK_HPP

#include "Token.hpp"
#include <string>
#include <vector>
// The implementation for all functions in OpenTagStack are stored in OpenTagStack.cpp

class OpenTagStack {
public:
    void addTag(const Token &token);  // add a new token to the top of the stack.
    bool empty();  // is the stack empty?
    bool findTagInStack(std::string tagName);
    Token top();   // returns the top element.
    // top writes an error message and terminates the application if stack is empty.
    void pop();    // removes the top element from the stack.
    // pop writes an error message and terminates the application if the stack is empty.
    // removeElementWithTagName searches the stack from top to bottom and
    // if there is a token whose tag-name matches tagName, that element
    // gets removed from the stack. If the element doesn't exist, this function
    // doesn't make any changes to the stack.
    void removeElementWithTagName(std::string tagName);
    void printStack(); // Use this function as a debugging tool to print all tokens that
    // are currently on the stack.

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
    void printTokensAbove(std::string tagName);


private:
    std::vector<Token> stack;
};


#endif //PROJECT1_PHASE2_OPENTAGSTACK_HPP
