//
// Created by xmani on 2/2/2023.
//
//
// Created by Ali Kooshesh on 1/22/23.
//

#include <iostream>
#include <string>
#include "Tokenizer.hpp"
//simple function that puts the fstream into the object

Tokenizer::Tokenizer(std::string name) : lineNumber{ 1 },
                                         charPosition{ 1 },
                                         inputFileName{ name } {
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

bool Tokenizer::charOfInterest(char c) {
    // is c the initial (or the sole) character of a token?
    // this code need to return true if a character of intrest is found such as an angle brack.
    if (c == '<') {
        return true;
    }
    else if (c == '>') {
        return true;

    }
    else if (c == '/') {
        if (inputStream.peek() == '>') {
            return true;
        }
        return false;

    }

    return false;   // you need to replace this with code that compares c with characters like '<', '>', etc.
}
// function that makes the token.
Token Tokenizer::getToken() {
    // temp char to store input comming from the fstream
    char c;
    //temp string variable for storing tag.
    std::string tempTag = "";
    // check to see if file is readable, if not printer error message.
    if (!inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }

    //initial setting of tag. this loop is mainly here so that the tag can be recieved and the proper input can be set as the program start for char c
    tempTag = getTokenTagName(c);

    // The above loop stops because one of its conditions is false. That means
    // either function get failed, which happens at the end of the file, or
    // c, the character that get read, is a character of interest. The other
    // possibility is if the input file was not open or the input somehow got clobbered.

    // makes a token with the given line number and char position.
    Token token(lineNumber, charPosition);
    //if we have reached the end of the file then we set the bool of current token to reflect that then we return token.
    if (inputStream.eof()) {
        token.endOfFile() = true;
        return token;
    }

    // Now, we go through a sequence of if ... else if statements
    // to identify the token whose first character we have just read. This is
    // the character that caused the while loop to terminate.

    if (c == '<') { // A possible open tag.
        // as long as we do not have a char of intrest we need to pipe in the input until we reach a char of intrest
        tempTag = getTokenTagName(c);
        // When this condition is ture, you need to
        // determine if it is immediately followed by a name, which means it is
        // an open tag, or a /, which means it might be a close tag, or it is a
        // random open angle-bracket. Here, to demonstrate how you make an open
        // tag token, we assume the input contained <em. That mean, we have
        // determined that it is a open tag (that there is a letter after the open
        // angle bracket, and that we have read the tag name, em, into a variable.
        // We use the variable that contains the name to create the token.
        //std::cout<<" "<<c<<": "<<this->charPosition<<std::endl;
        token.makeOpenTag(tempTag);
        token.endOfFile() = false;
        this->charPosition++;
        //important check to make sure that if we end on a / it is put back on the inputStream for processing in the next token
        // if / is not put back then close angle brace loses its slash.
        if (c == '/') {
            inputStream.putback(c);
        }
        return token;

    }
    else if (c == '/' && inputStream.peek() == '>') {
        tempTag = "";
        token.isCloseStandAloneTag() = true;
        tempTag += c;
        //std::cout << " " << c << ": " << this->charPosition << std::endl;
        this->charPosition ++;
        // grabs the next input since we know it is a >.
        inputStream.get(c);
        //std::cout << " " << c << ": " << this->charPosition << std::endl;
        this->charPosition++;
        token.makeCloseTag(tempTag);
        token.endOfFile() = false;
        return token;
    }
    else if (c == '>') {
        token.isCloseAngleBracket() = true;
        //std::cout<<" "<<c<<": "<<this->charPosition<<std::endl;
        inputStream.get(c);

        this->charPosition++;

        token.makeCloseTag(tempTag);
        token.endOfFile() = false;
        return token;
    }
        // ... more if-else statements here.
    else {
        // The condition of one of the above "if ... else if" statements should
        // evaluate to true because function charOfInterest return true when it
        // finds a character that is the start of some token and that the
        // "if ... else if" has one case for each character that starts a token.
        // Therefore, the control should never get here. However, it is always
        // a good idea to have an "else" when you have a sequence of "if ... else if"
        // statements so that you do not end up with a case that has not been handled.
        // For example, you forgot to account for one of the cases.
        std::cout << "There is a logic error in unction Tokenizer::getToken.\n";
        std::cout << "The function doesn't know how to process this character: ->" << c << "<-\n";
        exit(1);
    }

    return token; // The control SHOULD NOT reach this statement.
}

//function added to easily grab input of tag once a char of interest is found.
std::string Tokenizer::getTokenTagName(char& c) {
    //holds the tempTag within the function which is returned after the while loop retrieves the tag.
    std::string tempTag = "";
    //since we know that c is currently a char of intrest we pipe in the next input.
    //probably needs a if statement to protect it if the tag is empty. probably a peek to see if next char is a character if intrest.
    // as long as we do not have a char of intrest we need to pipe in the input until we reach a char of intrest
    //if (inputStream.peek() != '>') {
    // inputStream >> c;
    //}
    bool spaceFound = false;

    while (inputStream.get(c) && !charOfInterest(c)) {
        if (isspace(c)) {
            spaceFound = true;
        }
        if (spaceFound == false) {
            tempTag += c;
        }
        // pipes in the next input.
        //inputStream >> c;
        if (c == '\n') {
            //std::cout<<std::endl;
            this->lineNumber++;
            this->charPosition++;
        }
        else {
            this->charPosition++;
        }
        //std::cout << " " << c << ": " << this->charPosition << std::endl;


    }
    //std::cout << std::endl;
    //puts back close bracket if we find one after getting a tag back on the input stream.
    if (c == '>') {
        inputStream.putback(c);
    }

    return(tempTag);
}
