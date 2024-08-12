//
// Created by xmani on 2/2/2023.
//
//
// Created by Ali Kooshesh on 1/22/23.
//

#ifndef PROJECT1_PHASE2_COMPLETEDTAGS_HPP
#define PROJECT1_PHASE2_COMPLETEDTAGS_HPP

#include<iostream>
#include<map>
#include<vector>

#include "Token.hpp"

class CompletedTags {
public:

    // addCompletedTag takes two arguments
    //     -- an open tag and its corresponding close tag
    //  or
    //     -- an open tag and a stand-alon close tag

    // In either case, if the map doesn't have an entry for the tag-name,
    // you add a vector to the map using the tag name and add the two tokens
    // to the vector.
    // On the other hand, if the tag-name already exists in the map, you just add the two
    // token to its vector.
    void addCompletedTag(const Token &token1, const Token &token2);

    // The error messages get printed in the main function.
    // This function prints each completed tag and the locations
    // where the tag has been found in the input.
    void print();

private:
    //because map needs a way to seperate tags with the same name we will preplace the string with a pair
    // and use this int to create a number which can distinguish map items.
    int keyNumber = 0;

    typedef std::pair<std::string,int> key;

    //map now takes a struct and a vector
    std::map< key, std::vector<Token> > completedTags;
};


#endif //PROJECT1_PHASE2_COMPLETEDTAGS_HPP
