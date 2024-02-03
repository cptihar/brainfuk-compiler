#include <iostream>
#include <vector>

#include "Tokenizer.h"
#include "Parser.h"

#define LOG(message) std::cout << "[LOG] " << message << std::endl;


int main (int argc, char** argv) {

    std::vector<unsigned char> Instructions;

    // Tokenizer scope
    {
        bf::Tokenizer tokenizer(argv[1]);

        // Check whether a file was provided
        if (argc < 2) {
            LOG("Please provide a file");
            return EXIT_FAILURE;
        }

        // Check whether file exists
        else if (!tokenizer.fileOpen()) {
            LOG("Couldn't load file: " << argv[1]);
            return EXIT_FAILURE;
        }

        // Load the instructions
        Instructions = tokenizer.loadInstructions();
    }
    
    // Parser scope
    {
        bf::Parser parser = bf::Parser(Instructions);
        parser.parseInstructions();
        if (parser.hasBracketError()) {
            LOG("Parser: Bracket mismatch");
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}