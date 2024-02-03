#include <iostream>
#include <vector>

#include "Tokenizer.h"


#define LOG(message) std::cout << "[LOG] " << message << std::endl;


int main (int argc, char** argv) {

    std::vector<char> Instructions;

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

    return EXIT_SUCCESS;
}