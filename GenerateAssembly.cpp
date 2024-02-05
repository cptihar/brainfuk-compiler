#include "GenerateAssembly.h"

bf::GenerateAssembly::GenerateAssembly(std::vector<unsigned char> & instructions)
    :m_InstructionVectorRef(instructions), m_InstructionMapper(bf::InstructionMapper())
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
    // Iterate through the instructions
    for (auto instruction : m_InstructionVectorRef) {
        // Push back assembly code
        auto iterator = m_HashedFunctions.find(instruction);
        m_GeneratedAssembly.push_back(iterator->second());
    }
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
    m_HashedFunctions[BF_PTR_MOVE_LEFT] = std::bind(&bf::InstructionMapper::ptrMoveLeft, &m_InstructionMapper);
}