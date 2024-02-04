#include "Parser.h"

bf::Parser::Parser(std::vector<unsigned char>&  instructions)
    :m_InstructionVector(instructions),
     m_ErrorMessage(std::string())
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
* Return: bool
*   True -> Has bracket mismatch
*   False -> No mismatch
*
* ===============================================
*/
const bool bf::Parser::hasBracketError()
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
                m_ErrorMessage += P_BRACKET_ERROR_MSG; // Add error message
                return true;
            }
            bracketStack.pop(); // Pop the stack
        }
    }

    if (!bracketStack.empty()) {
        m_ErrorMessage += P_BRACKET_ERROR_MSG; // Add error message
        return true;
    }

    return false;
}


/*
* =====================================================
*
* Function responsible for handling negative pointer indexes
* Expands error message if a problem was found
*
* Return: bool
*   -> True: Has error
*   -> False: No error
*   
* =====================================================
*/
const bool bf::Parser::hasPtrIndexError()
{
    int indexNumber = 0;

    for (auto c : m_InstructionVector) {

        // Check whether current instruction manipulates the ptr index
        if (c == BF_PTR_MOVE_LEFT) --indexNumber;
        else if (c == BF_PTR_MOVE_RIGHT) ++indexNumber;

        // Check whether the index would be negative
        if (indexNumber < 0) {
            m_ErrorMessage += P_NEGINDEX_ERROR_MSG;
            return true;
        }
    }
    return false;
}