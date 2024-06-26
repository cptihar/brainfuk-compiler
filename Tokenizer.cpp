#include "Tokenizer.h"

bf::Tokenizer::Tokenizer(const char *FilePath)
    :m_Stream(FilePath, std::ios::in)
{
    m_initInstructionSet();
}

bf::Tokenizer::~Tokenizer()
{
    if (m_Stream.is_open())
        m_Stream.close();
}


/*
* ============================================
* 
* Function which returns whether the file was opened
*
* Return: const bool
*          -> True: file is open
*          -> False: File is not open
*
* ============================================
*/
const bool bf::Tokenizer::fileOpen()
{
    return m_Stream.is_open();
}


/*
* ==============================================================
*
* Functions responsible for loading the instructions
*
* It checks whether the stream is open 
*   -> If not it returns early
*
* Uses a hash set to check whether the current data should be inserted
* 
* Return: std::vector<unsigned char>
*   -> If file doesn't exist {'0'}
*   -> If exists, it returns the instructions
*
* ==============================================================
*/
std::vector<unsigned char> bf::Tokenizer::loadInstructions()
{
    // Check whether the file is open
    if (!m_Stream.is_open()) {
        return {'0'};
    }

    // Reserve space
    m_InstructionVector.reserve(DEFUALT_VECTOR_SIZE);


    // Read data
    char currentData;
    while (m_Stream.get(currentData)) {
        // Loop up current data
        if (m_InstructionSet.count(currentData))
            m_InstructionVector.emplace_back(currentData); // Place data

    }

    m_Stream.close(); // Close file

    return m_InstructionVector;
}


/*
* =======================================================
*
* This functions initializes the InstructionSet
* Contains the constants defined in BrainfuckConstants.h
*
* Return: void
*
* =======================================================
*/
void bf::Tokenizer::m_initInstructionSet()
{
    m_InstructionSet.insert(BF_PTR_MOVE_LEFT);
    m_InstructionSet.insert(BF_PTR_MOVE_RIGHT);
    m_InstructionSet.insert(BF_DATA_INCREMENT);
    m_InstructionSet.insert(BF_DATA_DECREMENT);
    m_InstructionSet.insert(BF_DATA_PRINT);
    m_InstructionSet.insert(BF_DATA_INPUT);
    m_InstructionSet.insert(BF_LOOP_START);
    m_InstructionSet.insert(BF_LOOP_END);
}