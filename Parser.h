#ifndef BRAINFUCK_PARSER_H
#define BRAINFUCK_PARSER_H

#include <vector>
#include <stack>
#include <string>

#include "BrainfuckConstants.h"

#define P_BRACKET_ERROR_MSG   "\nBracket mismatch\n"
#define P_NEGINDEX_ERROR_MSG  "\nNegative pointer index\n"

namespace bf 
{
    class Parser 
    {
        public:
            Parser(std::vector<unsigned char>& instructions);
            ~Parser();

            const bool  hasBracketError();
            const bool  hasPtrIndexError();

            std::string  getErrorMessage() { return m_ErrorMessage; }

        private:
            // Variables
            std::vector<unsigned char>&  m_InstructionVector;
            std::string                  m_ErrorMessage;
        
    };
}
#endif // !BRAINFUCK_PARSER_H