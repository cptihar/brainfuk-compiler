#include "GenerateAssembly.h"

bf::GenerateAssembly::GenerateAssembly(const std::vector<unsigned char> &instructions)
    :m_BfInstructionRef(instructions),
     m_AsmInstructions(bf::AssemblyInstructions())
{
    // Initialize hash map
    m_initializeHashMap();
}

bf::GenerateAssembly::~GenerateAssembly()
{}


/*
* =================================
* 
* Iterates through the instructions
* Generates the assembly code
*
* Return: void
*
* =================================
*/
void bf::GenerateAssembly::createAssembly()
{
    // Setup assembly
    m_appendGeneratedCode(m_AsmInstructions.beginAssembly(m_calculateTapeSize()));
    
    // Generate assembly for BF instructions
    std::stack<size_t> jumpStack;
    for (auto c : m_BfInstructionRef) {

        if (c == BF_LOOP_START) {
            jumpStack.push(m_GeneratedAssembly.size()-1);
        }

        else if (c == BF_LOOP_END) {
            m_handleBfLoopInstruction(jumpStack.top());
            jumpStack.pop();
        }

        else {
            auto it = m_InstructionHashes.find(c);
            m_appendGeneratedCode(it->second());
        }
    }

    // Generate program exit
    m_appendGeneratedCode(m_AsmInstructions.endAssembly());
}


/*
* =====================================================
*
* Dumps the assembly code generated by createAssembly()
* Opens the file given by fpath
* Cleans up the resources used
*
* Checks whether the file exists:
*       -> If not returns, doesnt notify
* 
* Return: void
*
* =====================================================
*/
void bf::GenerateAssembly::dumpAssembly(const char *fpath)
{
    std::ofstream outStream (fpath);

    // Check whether file is opened
    if (!outStream.is_open()) return;

    // Dump assembly code to file
    for (auto& k : m_GeneratedAssembly)
        outStream << k << "\n";

    outStream.close(); // Cleanup resource
}


/*
* ================================
*
* Calculates the maximum tape size
*
* Return: uint32_t
*
* ================================
*/
uint32_t bf::GenerateAssembly::m_calculateTapeSize()
{
    uint32_t finalSize = 1;
    uint32_t currentSize = 1;

    for (auto c : m_BfInstructionRef) {

        // Check whether instruction pointer moves left
        if (c == BF_PTR_MOVE_RIGHT) {
            ++currentSize;

            // Check whether the current size is bigger
            if (currentSize > finalSize)
                finalSize = currentSize; // Update final size
        }

        // Check whether instruction pointer moves right
        else if (c == BF_PTR_MOVE_LEFT) {
            --currentSize;
        }
    }
    return finalSize;
}


/*
* ======================================================
*
* Initializes the hash map
* Binds BF instructions to their corresponding functions
*
* Return: void
*
* ======================================================
*/
void bf::GenerateAssembly::m_initializeHashMap()
{
    // Bind ptr manipulators
    m_InstructionHashes[BF_PTR_MOVE_LEFT]  = std::bind(&bf::AssemblyInstructions::ptrMoveLeft, &m_AsmInstructions);
    m_InstructionHashes[BF_PTR_MOVE_RIGHT] = std::bind(&bf::AssemblyInstructions::ptrMoveRight, &m_AsmInstructions);

    // Bind data manipulators
    m_InstructionHashes[BF_DATA_INCREMENT] = std::bind(&bf::AssemblyInstructions::dataIncrement, &m_AsmInstructions);
    m_InstructionHashes[BF_DATA_DECREMENT] = std::bind(&bf::AssemblyInstructions::dataDecrement, &m_AsmInstructions);

    // Bind Input, output
    m_InstructionHashes[BF_DATA_INPUT] = std::bind(bf::AssemblyInstructions::ioInput, &m_AsmInstructions);
    m_InstructionHashes[BF_DATA_PRINT] = std::bind(bf::AssemblyInstructions::ioPrint, &m_AsmInstructions);
}


/*
* ======================================
*
* Appends generated assembly code to the instructions vector
* Doesn't handle loop instructions!!!!!!
*
* Return: void
*
* ======================================
*/
void bf::GenerateAssembly::m_appendGeneratedCode(const SVEC &data)
{
    for (auto d : data) {
        m_GeneratedAssembly.push_back(d);
    }
}


/*
* ========================================
*
* Handles the loop instructions by:
*   1. Calculating the offset for the jump
*   2. Inserts the ASM instructions
*
* Return: void
*
* ========================================
*/
void bf::GenerateAssembly::m_handleBfLoopInstruction(size_t loopStartIndex)
{
    // Variables to calculate the jump positions
    const uint8_t lineSize = (m_AsmInstructions.loopBegin(std::to_string(2)).size() + m_AsmInstructions.loopEnd(std::to_string(2)).size()) / 2; // Asm line size
    size_t jumpSize = m_GeneratedAssembly.size() - loopStartIndex + lineSize;


    // Helper variables for forward jump
    auto insertpos = m_GeneratedAssembly.begin() + loopStartIndex + 1;
    size_t counter = 0;

    // Dump forward jump
    for (auto& s : m_AsmInstructions.loopBegin(std::to_string(jumpSize))) {
        m_GeneratedAssembly.insert(insertpos+counter, s);
        ++counter;
    }

    // Dump backward jumps
    for (auto& s : m_AsmInstructions.loopEnd(std::to_string(jumpSize))) {
        m_GeneratedAssembly.push_back(s);
    }
}