//
// Created by xmani on 2/2/2023.
//
//
// Created by Ali Kooshesh on 1/22/23.
//
#include "CompletedTags.hpp"
//adds completed map items to the map
void CompletedTags::addCompletedTag(const Token &token1, const Token &token2) {
    //creates a temp vector
    std::vector<Token> tempVector;
    // pushes tokens onto the temp vector
    tempVector.push_back(token1);
    tempVector.push_back(token2);
    //now that tokens are on the temp vector we can grab the tag name from the first token.
    std::string tagID = tempVector.at(0).tagName();

    //incriment keyNumber;
    keyNumber++;
    //get the tag name and set it to the key
    key currentKey(tagID,keyNumber);

    //expects a a key which contains a string tag name and a distinguishing int, then the vector that stores the open and close tag.
    completedTags[currentKey] = tempVector;

    //loop used for testing purposes. helped me discover that maps will over write values if they have the same key. using a pair we fix this issue
    //without losing the effective organization of a map.
    /*for (auto mapIter = completedTags.begin(); mapIter != completedTags.end(); ++mapIter) {
        // our map, pairs an array of Tokens with tag-name strings.
        std::vector<Token> locations = mapIter->second;
        for (std::vector<Token>::iterator vIter = locations.begin();
            vIter != locations.end(); ++vIter) {
            vIter->print();
            std::cout << std::endl;
        }
    }*/

}

//spits out completed tags after parser has finished.
void CompletedTags::print() {
    std::cout << std::endl;

    std::cout<< "The following is a list of well-formed HTML tags." << std::endl;

    std::cout << std::endl;

    std::vector<Token> tempContainer;
    int tagAmount = 0;

    // Use an iterate to step through all elements of maps
    for (auto mapIter = completedTags.begin(); mapIter != completedTags.end(); ++mapIter) {
        // our map, pairs an array of Tokens with tag-name strings.
        std::vector<Token> locations = mapIter->second;
        for (std::vector<Token>::iterator vIter = locations.begin();vIter != locations.end(); ++vIter) {
            // spits out token
            //vIter->print();
            //puts current token in iterato,  asterisk used to get data out of iterator rather than memory adress because vIter is a pointer.
            tempContainer.push_back(*vIter);

            // increments key value apart of the data type so that we can distinguish tags with the same tag name.
            if (tempContainer.at(tempContainer.size() - 1).isCloseTag() || tempContainer.at(tempContainer.size() - 1).isCloseStandAloneTag()) {
                tagAmount++;
            }
            // while adding tokens to our temp vector if we find a token with a tag that does
            //not match we need to empty the vector after printing the amount of that tag found
            //and the tags themeselves

            //print out TAGS if the current tag is not matching the tag in the vector and it is not a close or stand alone tag.
            if (tempContainer.at(tempContainer.size()-1).tagName() != tempContainer.at(0).tagName() && tempContainer.size() != 0 && !tempContainer.at(tempContainer.size() - 1).isCloseStandAloneTag() && !tempContainer.at(tempContainer.size() - 1).isCloseStandAloneTag()) {
                std::cout << tempContainer.at(0).tagName()<< " appeared in the following "<< tagAmount <<" locations." << std::endl;
                //loop then spits out tokens and removes them from the vector
                //errases the last item out of the vector because it is not apart of the current print tags
                tempContainer.erase(tempContainer.begin()+ tempContainer.size() - 1);
                //spits out tags in temp vector and emptys the value in the back at 0
                // continues till the vector is empty
                while (tempContainer.size() != 0) {
                    if (tempContainer.at(0).isOpenTag()) {
                        std::cout << "       ";
                        tempContainer.at(0).print();
                        std::cout << " -- ";
                    }else {
                        tempContainer.at(0).print();
                        std::cout << std::endl;
                    }
                    tempContainer.erase(tempContainer.begin());
                }
                std::cout << std::endl;
                tagAmount = 0;
                tempContainer.push_back(*vIter);
            }

        }
    }
    //after we are done iterating there is going to be one group of tags left over that needs to be printed. so we repeat the same code above
    // to print out that last group but without removing the last element put on the vector.
    std::cout << tempContainer.at(0).tagName() << " appeared in the following " << tagAmount << " locations." << std::endl;

    while (tempContainer.size() != 0) {
        if (tempContainer.at(0).isOpenTag()) {
            std::cout << "       ";
            tempContainer.at(0).print();
            std::cout << " -- ";
        }
        else {
            tempContainer.at(0).print();
            std::cout << std::endl;
        }
        tempContainer.erase(tempContainer.begin());
    }
    std::cout << std::endl;
}
