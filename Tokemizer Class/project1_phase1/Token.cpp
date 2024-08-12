//
// Created by xmani on 2/2/2023.
//
//
// Created by Ali Kooshesh on 1/22/23.
//

#include <iostream>
#include <iomanip>
#include "Token.hpp"

Token::Token(int line, int pos) {
    _isOpenTag = false;
    _isCloseTag = false;
    _isCloseAngleBracket = false;
    _isOpenAngleBracket = false;
    _isCloseStandAloneTag = false;
    _tagName = "";
    _lineNumber = line;
    _charPos = pos;
}

bool &Token::isOpenTag() { return _isOpenTag; }
bool &Token::isCloseTag() { return _isCloseTag; }

bool &Token::isCloseAngleBracket() { return _isCloseAngleBracket; }

bool &Token::endOfFile() { return _eof; }
bool &Token::isCloseStandAloneTag() { return _isCloseStandAloneTag; }

std::string Token::tagName() { return _tagName; }

void Token::makeOpenTag(std::string name) {
    _tagName = name;
    isOpenTag() = true;
}

void Token::makeCloseTag(std::string name) {
    _tagName = name;
    isCloseTag() = true;
}

void Token::print() {
    std::cout << "[" << std::setw(2) << _lineNumber << ", " <<  std::setw(3) << _charPos << "] ";

    // You should have one condition for each of the token types that you
    // this class can hold.
    if(isOpenTag()) {
        std::cout << "<" << tagName() << std::endl;
    }else if (isCloseTag()) {
        std::cout << tagName() << ">" << std::endl;
    }else if(isCloseStandAloneTag()) {
        //std::cout << "[" << _lineNumber << ", " << _charPos << "] ";
        std::cout << tagName() << "/>"<< std::endl;
    } else {
        std::cout << "Token::print -- unknown token.\n" << std::endl;
        exit(3);
    }

}

