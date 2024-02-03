#ifndef BRAINFUCK_PARSER_H
#define BRAINFUCK_PARSER_H

#include <vector>
#include <stack>

#include "BrainfuckConstants.h"

namespace bf {
    class Parser {
        public:
            Parser(std::vector<unsigned char>& instructions);
            ~Parser();

            void        parseInstructions();
            const bool  hasBracketError() { return m_hasBracketError; }

        private:
            // Variables
            std::vector<unsigned char>&  m_InstructionVector;
            bool                         m_hasBracketError;
    };
}
#endif // !BRAINFUCK_PARSER_H