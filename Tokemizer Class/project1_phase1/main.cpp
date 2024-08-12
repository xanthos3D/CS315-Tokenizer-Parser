#include <iostream>
#include <fstream>
#include "Tokenizer.hpp"
#include<stack>

using namespace std;

void parser(Tokenizer& tempTokenizer);

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
    //string fileName = "project1_phase1_sample_input_2.txt";
    //gets file name from user, for testing purposes.

    Tokenizer tokenizer(argv[1]);   // use the first argument, which contains the name of the input file
    //Tokenizer tokenizer(fileName);
    // to create an instance of Tokenizer.
    //Token token = tokenizer.getToken();  // get the first token.

    //token.print();
    parser(tokenizer);

    /*
     * this is what the main function for your solution to phase 1 should look like.

    Tokenizer tokenizer(argv[1]);
    // in lecture code giving the token cause a problem where it was not added to the stack because the call to the function
    //handling it initilized token with another value before the first one could be added to the stack. be warry of this.
    Token token = tokenizer.getToken();  // get the first token to start the while loop

    while( ! token.endOfFile() ) {
        token.print();
        token = tokenizer.getToken();
    }
     */

    return 0;
}
// current parser function which prints out the tokens. does not do any parsing yet.
void parser(Tokenizer& tempTokenizer) {

    stack<Token> stack;

    Token tempToken = tempTokenizer.getToken();
    while (!tempToken.endOfFile()) {
        // prints each token
        tempToken.print();

        tempToken = tempTokenizer.getToken();
    }
}
