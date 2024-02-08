#include "GenerateAssembly.h"

bf::GenerateAssembly::GenerateAssembly(std::vector<unsigned char> & instructions)
    :m_InstructionVectorRef(instructions), m_AsmInstructions(bf::AssemblyInstructions())
{
    m_InitBrutalHashMap();
}

bf::GenerateAssembly::~GenerateAssembly()
{}


/*
* ===================================================
*
* Function responsible for creating the assembly code
* Doesn't dump it into a file
* Uses hash map to add the instructions to the vector
*
* Return void
*
* ===================================================
*/
void bf::GenerateAssembly::createAssembly()
{
    m_GeneratedAssembly.push_back(m_AsmInstructions.beginAssembly(30));
    
    // Iterate through the instructions
    for (auto instruction : m_InstructionVectorRef) {
        // Push back assembly code
        auto iterator = m_HashedFunctions.find(instruction);
        m_GeneratedAssembly.push_back(iterator->second());
    }

    m_GeneratedAssembly.push_back(m_AsmInstructions.endAssembly());
}


/*
* =======================================================
*
* Function responsible for dumping the generated assembly
* 
* The file is opened by the function;
*    -> Whether the file exists or not should be checked before calling the function
*
* Handles resource cleanup (opened file)
*
* Return: void
*
* =======================================================
*/
void bf::GenerateAssembly::dumpAssembly(const char *fileName)
{
    // Open file
    std::ofstream outStream = std::ofstream(fileName);

    // Dump assembly
    if (outStream.is_open()) {
        for (auto& s : m_GeneratedAssembly) {
            outStream << s << '\n';
        }
    }
    else return;

    // Close file
    outStream.close();
}


/*
* ========================================================
* 
* Function responsible for initialzing m_HashedFunctions
* 
* Binds the instructions with the corresponding functions
*
* Return: void
*
* ========================================================
*/
void bf::GenerateAssembly::m_InitBrutalHashMap()
{
    // Instruction pointer manipulators
    m_HashedFunctions[BF_PTR_MOVE_LEFT]  = std::bind(&bf::AssemblyInstructions::ptrMoveLeft, &m_AsmInstructions);
    m_HashedFunctions[BF_PTR_MOVE_RIGHT] = std::bind(&bf::AssemblyInstructions::ptrMoveRight, &m_AsmInstructions);

    // Data manipulators
    m_HashedFunctions[BF_DATA_DECREMENT] = std::bind(&bf::AssemblyInstructions::dataDecrement, &m_AsmInstructions);
    m_HashedFunctions[BF_DATA_INCREMENT] = std::bind(&bf::AssemblyInstructions::dataIncrement, &m_AsmInstructions);

    // Input, output
    m_HashedFunctions[BF_DATA_INPUT] = std::bind(&bf::AssemblyInstructions::ioInput, &m_AsmInstructions);
    m_HashedFunctions[BF_DATA_PRINT] = std::bind(&bf::AssemblyInstructions::ioPrint, &m_AsmInstructions);

    // Loops
    m_HashedFunctions[BF_LOOP_START] = std::bind(&bf::AssemblyInstructions::loopBegin, &m_AsmInstructions);
    m_HashedFunctions[BF_LOOP_END]   = std::bind(&bf::AssemblyInstructions::loopEnd, &m_AsmInstructions);
}