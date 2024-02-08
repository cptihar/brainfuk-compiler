#include <iostream>
#include <vector>

#include "Tokenizer.h"
#include "Parser.h"
#include "GenerateAssembly.h"

#define LOG(message) std::cout << "[LOG] " << message << std::endl;


int main (int argc, char** argv) {

    std::vector<unsigned char> Instructions;

    // Tokenization phase
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
    
    // Parsing phase
    {
        // Parse code
        bf::Parser parser = bf::Parser(Instructions);

        // Check whether there are errors
        if (parser.hasBracketError() || parser.hasPtrIndexError()) {
            LOG("Parser error! " + parser.getErrorMessage());
            return EXIT_FAILURE;
        }
    }
    
    // Assembly generation phase
    bf::GenerateAssembly AssemblyGenerator = bf::GenerateAssembly(Instructions);
    
    // Check whether file name was provided
    if (argc < 3) {
        LOG("Please provide an output file name!");
        return EXIT_FAILURE;
    }

    // Create assembly
    AssemblyGenerator.createAssembly();

    // Dump assembly
    AssemblyGenerator.dumpAssembly(argv[2]);

    return EXIT_SUCCESS;
}