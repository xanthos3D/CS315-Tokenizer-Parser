//
// Created by xmani on 2/2/2023.
//
//
// Created by Ali Kooshesh on 1/22/23.
//
#include <iostream>
#include <fstream>
#include "Tokenizer.hpp"
#include<stack>
#include"OpenTagStack.hpp"
#include"CompletedTags.hpp"

using namespace std;
void parser(Tokenizer& tempTokenizer);
// functions to handle the open and close tags as they come into the parser.
void handleOpenTag(Tokenizer& tempTokenizer,Token& token, OpenTagStack& openTagStack, CompletedTags& completedTags);
void handleCloseTag(Tokenizer& tempTokenizer, Token& token, OpenTagStack& openTagStack, CompletedTags& completedTags);

int main(int argc, char *argv[]) {

    if (argc != 2) {  // we expect the name of the file as an argument to the program.
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile" << std::endl;
        exit(1);
    }

    // Here, we open the file to make sure that it exists before starting the program.
    // When using CLion, the input file has to be in cmake-build-debug directory.
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);    // open for reading
    if( ! inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        //std::cout << strerror(errno) << std::endl;
        exit(2);
    }

    // We now know that the input file exists and we can read from it. Here, we will close it
    // and give Tokenizer the name of the file so it can open and use it. We also could give
    // Tokenizer 'inputStream' so that it just uses it.
    inputStream.close();
    //string fileName = "sampleInput2.txt";
    //gets file name from user, for testing purposes.

    Tokenizer tokenizer(argv[1]);   // use the first argument, which contains the name of the input file
    //Tokenizer tokenizer(fileName);
    // to create an instance of Tokenizer.
    //Token token = tokenizer.getToken();  // get the first token.

    //parser takes tokens and verifys them, storing completed tags and displaying them.
    parser(tokenizer);

    return 0;
}

void parser(Tokenizer& tempTokenizer) {
    // data types to help store our completed tokens and process tokens
    CompletedTags completedTags;
    OpenTagStack openTagStack;

    Token tempToken = tempTokenizer.getToken();

    // temp while loop for testing purposes
    /*while (!tempToken.endOfFile()) {
        tempToken.print();
        cout << endl;
        tempToken = tempTokenizer.getToken();
    }*/

    //the tokenizer expectes a open token followed by a closed token. <em then >.
    //also keep in mind when there is a open, closed, and stand alone tag <em> ... </em>
    while (!tempToken.endOfFile()) {
        // if a open tag is found we want to call our open tag function to handle it
        if (tempToken.isOpenTag()) {// handles <em>
            handleOpenTag(tempTokenizer, tempToken, openTagStack, completedTags);

        }
            //if a close tag is found we want to handle that in our close tag function
        else if (tempToken.isCloseTag()) {// handles </em>
            handleCloseTag(tempTokenizer, tempToken, openTagStack, completedTags);

        }
            //if we find a open or close bracket not in one of our open or close tag function then it is a
            //random open angle bracked or randome close angle bracket so print an error message
        else if (tempToken.isCloseAngleBracket() || tempToken.isOpenAngleBracket()) {
            tempToken.print();
            if (tempToken.isCloseAngleBracket()) {
                std::cout << " ignoring random close angle-bracket." << std::endl;
            }
            else if (tempToken.isOpenAngleBracket()) {
                std::cout <<" ignoring random open angle-bracket." << std::endl;
            }
            tempToken = tempTokenizer.getToken();
        }
            // some how found a token we cant read. should NEVER reach here
        else {
            tempToken.print();
            std::cout << " unknown token." << std::endl;
            exit(1);
        }
    }

    //now to print the completed tags
    completedTags.print();
}

// function has many cases to catch if a tag is correctly formed as a open tag or incorrectly formed.
void handleOpenTag(Tokenizer& tempTokenizer, Token& token, OpenTagStack& openTagStack, CompletedTags& completedTags) {
    // make a temperary token to store the current token. we expect the next token to be a close angle brace
    Token previousToken = token;
    // gets the next token
    token = tempTokenizer.getToken();
    // if the token is an open tag / open brace then print an error
    if (token.isOpenAngleBracket()) {
        previousToken.print();
        cout << " is missing a '>' or '/>'. Will discard it." << endl;
        // so we will trash this token but not get a new input. the next intput could be valid but if its just a open brace with no tag our
        //parser will catch that
    }
        //if we find a close angle brace then we have found a properly formed opening tag
    else if (token.isCloseAngleBracket()) {

        //push previous token onto opentagstack
        openTagStack.addTag(previousToken);

        //openTagStack.printStack();
        //grabbs next input
        token = tempTokenizer.getToken();
    }
        // if we find a stand alone close tag things need to be handled a little differently.
    else if (token.isCloseStandAloneTag()) {

        // if we find a stand alone tag closer then we want to add that stand alone tag to the completed tag map as it is exclusive.

        completedTags.addCompletedTag(previousToken, token);

        //openTagStack.printStack();

        //grabs next token.
        token = tempTokenizer.getToken();
    }
}

//function for handling close tags.
void handleCloseTag(Tokenizer& tempTokenizer, Token& token, OpenTagStack& openTagStack, CompletedTags& completedTags) {

    // just like handle open tag we want to store the current closing tag in a temp token and grab the next input to see if it is a closing brace
    Token previousToken = token;
    //token.print();
    token = tempTokenizer.getToken();
    // if the token is an open brace we dont want to do anything and let the parser handle it.
    if (token.isOpenAngleBracket()) {
        //cout << " [found a open angle bracket after another open angle bracket that was a close brace]" << endl;

    }
        // if we find a close angle bracket then we need to see if the closing tag is properly formed.
    else if (token.isCloseAngleBracket()) {

        //since this is a closing brace to a closetag we need to check if the stack has a open tag that matches this closing tags tag name
        if (!openTagStack.empty() && openTagStack.top().tagName() == previousToken.tagName()) {

            //first we should make a item in our copmleted tags map storing the two token that form a proper nested tag.
            completedTags.addCompletedTag(openTagStack.top(),previousToken);
            // then we need to pop to remove the top of the stack and the current close tag as it was correctly nested and stored in completetags
            openTagStack.pop();

            // then get next input
            token = tempTokenizer.getToken();

        }
            //else if we find a closetag but there is nothing in the stack we need to trash it and print an error
            // if the top of the stack is a close angle brace then this close tag is invalid so we need to throw away the last token on the stack and the current one
        else if (openTagStack.empty()) {
            previousToken.print();
            cout << " (with close angle bracket ";
            token.print();
            cout << ") doesn't have a matching open tag. Will discard it." << endl;

            token = tempTokenizer.getToken();

        }
            //if the stack is not empty and the token found is a open angle brace then we remove the top of the stack and print an error message.
        else if (!openTagStack.empty() && token.isOpenAngleBracket()) {
            previousToken.print();
            cout << " is missing a '>' or '/>'. Will discard it." << endl;
            openTagStack.pop();

        }
            //if we find a closing tag that closes properly but gets caught here that means that it does not match the tag name with the
            //open tag at the top of openstack. we also need to determine if a tag closes prematurely here.
        else if (token.isCloseAngleBracket()) {
            // if a proper closing brace is found for the current closed tag but the close tag does not match the open tag on the stack then
            // we need to see if the current close tag matches something in the stack so we can remove that element as well or ignore that element if
            // the tag cannot be found.
            if (openTagStack.findTagInStack(previousToken.tagName()) ) {
                // prints out error and tags above it
                previousToken.print();
                std::cout << " closes while the following tags remain open." << std::endl;
                openTagStack.printTokensAbove(previousToken.tagName());
                // removes problematic tag in the stack
                openTagStack.removeElementWithTagName(previousToken.tagName());
            }
            else {
                previousToken.print();
                cout << " (with close angle bracket ";
                token.print();
                cout << ") doesn't have a matching open tag. Will discard it." << endl;
            }
            token = tempTokenizer.getToken();
        }


    }
}