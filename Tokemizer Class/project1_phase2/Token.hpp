//
// Created by xmani on 2/1/2023.
//
//
// Created by Ali Kooshesh on 1/22/23.
//

#ifndef PROJECT1_PHASE2_TOKEN_HPP
#define PROJECT1_PHASE2_TOKEN_HPP


#include <string>

class Token {
public:
    Token(int, int);
    bool &isOpenTag();
    bool &isCloseTag();

    bool &isCloseAngleBracket();
    bool &isOpenAngleBracket();

    void setCloseAngleBracket();
    void setOpenAngleBracket();

    bool &endOfFile();
    bool &isCloseStandAloneTag();

    std::string tagName();

    void makeOpenTag(std::string);
    void makeCloseTag(std::string);
    void makeCloseStandAloneTag();
    void makeOpenAngleBracket();
    void makeCloseAngleBracket();
    void print();

private:
    bool _isOpenTag, _isCloseTag, _isCloseAngleBracket, _isOpenAngleBracket,
            _eof, _isCloseStandAloneTag;

    std::string _tagName;
    int _lineNumber, _charPos;
};

#endif //PROJECT1_PHASE2_TOKEN_HPP
