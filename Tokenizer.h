#ifndef BF_TOKENIZER_H
#define BF_TOKENIZER_H

#include <fstream>
#include <unordered_set>
#include <vector>

#include "BrainfuckConstants.h"

#define DEFUALT_VECTOR_SIZE  2000

namespace bf {

    class Tokenizer {
        public:
            Tokenizer() = default;
            Tokenizer(const char* FilePath);
            ~Tokenizer();

            const bool                  fileOpen();
            std::vector<unsigned char>  loadInstructions();

        private:
            // Variables
            std::ifstream                      m_Stream;
            std::vector<unsigned char>         m_InstructionVector;
            std::unordered_set<unsigned char>  m_InstructionSet;

        private:
            // Functions
            void  m_initInstructionSet();
    };
    
}
#endif // !BF_TOKENIZER_H