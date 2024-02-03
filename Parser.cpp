#include "Parser.h"

bf::Parser::Parser(std::vector<unsigned char>&  instructions)
    :m_InstructionVector(instructions),
     m_hasBracketError(false)
{}

bf::Parser::~Parser()
{}


/*
* ===============================================
*
* Function responsible for parsing the instruction vector
*
* Responsible for:
*   -> Spotting bracket errors
*   -> If there are errors set the m_hasError variable to true
*
* Return: void
*
* ===============================================
*/
void bf::Parser::parseInstructions()
{
    std::stack<unsigned char> bracketStack;
    
    for (auto c : m_InstructionVector) {

        // Check for opening bracket
        if (c == BF_LOOP_START)
            bracketStack.push(c);

        // Check for closing bracket
        else if (c == BF_LOOP_END) {

            // Check whether stack is empty
            if (bracketStack.empty()) {
                m_hasBracketError = true;
                return;
            }
            bracketStack.pop(); // Pop the stack
        }
    }

    if (!bracketStack.empty())
        m_hasBracketError = true;
}