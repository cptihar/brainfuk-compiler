#include "AssemblyInstructions.h"


bf::AssemblyInstructions::~AssemblyInstructions() {}


/*
* ===================================================
*
* Function responsible for setting up the code
* It defines the tape's size
* It sets the instruction pointer to the beginning
* Initializes _start
* 
* Return: std::vector<std::string> (SVEC)
*
* ===================================================
*/
SVEC bf::AssemblyInstructions::beginAssembly(uint32_t tapeSize)
{
        SVEC instructions;
        instructions.push_back(".intel_syntax noprefix");
        instructions.push_back(".section .data");
        instructions.push_back("    tape: .zero " + std::to_string(tapeSize));
        instructions.push_back(".section .text");
        instructions.push_back(".global _start");
        instructions.push_back("_start:");
        instructions.push_back("    mov ebx, OFFSET tape");
        return instructions;
}


/*
* ===========================================================
*
* Function responsible for generating the program's exit code
*
* Return: std::vector<std::string> (SVEC)
*
* ===========================================================
*/
SVEC bf::AssemblyInstructions::endAssembly()
{
    SVEC instructions;
    instructions.push_back("    mov eax, 1"); 
    instructions.push_back("    xor ebx, ebx");
    instructions.push_back("    int 0x80");
    return instructions;
}


/*
* =============================================================
*
* Function responsible for decrementing the instruction pointer
* Generates the code for it
*
* Return: std::vector<std::string>
*
* =============================================================
*/
SVEC bf::AssemblyInstructions::ptrMoveLeft()
{
    return {"    sub ebx, 1"};
}


/*
* =============================================================
*
* Function responsible for incrementing the instruction pointer
* Generates the code for it
*
* Return: std::vector<std::string>
*
* =============================================================
*/
SVEC bf::AssemblyInstructions::ptrMoveRight()
{
    return {"    add ebx, 1"};
}


/*
* =============================================================
*
* Function responsible for incrementing the data at the instruction pointer
* Generates the code for it
*
* Return: std::vector<std::string> (SVEC)
*
* =============================================================
*/
SVEC bf::AssemblyInstructions::dataIncrement()
{
    return {"    add byte ptr [ebx], 1"};
}


/*
* =============================================================
*
* Function responsible for decrementing the data at the instruction pointer
* Generates the code for it
*
* Return: std::vector<std::string> (SVEC)
*
* =============================================================
*/
SVEC bf::AssemblyInstructions::dataDecrement()
{
    return {"    sub byte ptr [ebx], 1"};
}


/*
* =======================================
*
* Function responsible for input handling
* Generates the assembly code for it
*
* Return: std::vector<std::string> (SVEC)
*
* =======================================
*/
SVEC bf::AssemblyInstructions::ioInput() {
    SVEC instructions;
    instructions.push_back("    mov eax, 3");
    instructions.push_back("    mov ecx, ebx");
    instructions.push_back("    mov edx, 1");
    instructions.push_back("    int 0x80");
    return instructions;
}


/*
* ==========================================================
* 
* Function responsible for handling the printing instruction
* Generates the code for it
*
* Return: std::vector<std::string> (SVEC)
*
* ==========================================================
*/
SVEC bf::AssemblyInstructions::ioPrint()
{
    SVEC instructions;
    instructions.push_back("    mov eax, 4");
    instructions.push_back("    mov ecx, ebx");
    instructions.push_back("    mov edx, 1");
    instructions.push_back("    int 0x80");
    return instructions;
}


/*
* ===============================================
*
* Generates the assembly code for '[' instruction
* 
* Return: std::vector<std::string> (SVEC)
*
* ===============================================
*/
SVEC bf::AssemblyInstructions::loopBegin(const std::string& jumpForward)
{
    SVEC instructions;
    instructions.push_back("    cmp byte ptr [ebx], 0");
    instructions.push_back("    je " + jumpForward);
    return instructions;
}


/*
* ===============================================
*
* Generates the assembly code for ']' instruction
* 
* Return: std::vector<std::string> (SVEC)
*
* ===============================================
*/
SVEC bf::AssemblyInstructions::loopEnd(const std::string& jumpBackPosition)
{
    SVEC instructions;
    instructions.push_back("    cmp byte ptr [ebx], 0");
    instructions.push_back("    jne " + jumpBackPosition);
    return instructions;
}