#include "AssemblyInstructions.h"

bf::AssemblyInstructions::~AssemblyInstructions()
{}


/*
* ===================================================
*
* Function responsible for setting up the code
* It defines the tape's size
* It sets the instruction pointer to the beginning
* Initializes _start
* 
* Return: std::string
*
* ===================================================
*/
std::string bf::AssemblyInstructions::beginAssembly(uint32_t tapeSize)
{
    std::string ret;
    ret += "section .data\n";
    ret += "   tape_size equ " + std::to_string(tapeSize) + "\n";
    ret += "   pointer dq 0\n";
    ret += "\nsection .bss\n";
    ret += "   tape resb tape_size\n";

    ret += "\nsection .text\n";
    ret += "   global _start\n";

    ret += "\n_start:\n";
    ret += "   cld\n";
    ret += "   mov edi, tape\n";
    ret += "   mov [pointer], edi\n";
    ret += "   ; End of assembly setup\n";
    ret += "   ; Start of brainfuck code\n\n";

    return ret;
}


/*
* ===========================================================
*
* Function responsible for generating the program's exit code
*
* Return: std::string
*
* ===========================================================
*/
std::string bf::AssemblyInstructions::endAssembly()
{
    std::string ret;

    ret += "\n\n   ; End of brainfuck code\n";
    ret += "   ; Close program\n\n";
    ret += "   mov eax, 1\n";
    ret += "   xor ebx, ebx\n";
    ret += "   int 0x80";

    return ret;
}


/*
* =============================================================
*
* Function responsible for decrementing the instruction pointer
* Generates the code for it
*
* Return: std::string
*
* =============================================================
*/
std::string bf::AssemblyInstructions::ptrMoveLeft()
{
    return "   dec edi";
}


/*
* =============================================================
*
* Function responsible for incrementing the instruction pointer
* Generates the code for it
*
* Return: std::string
*
* =============================================================
*/
std::string bf::AssemblyInstructions::ptrMoveRight()
{
    return "   inc edi";
}


/*
* =============================================================
*
* Function responsible for incrementing the data at the instruction pointer
* Generates the code for it
*
* Return: std::string
*
* =============================================================
*/
std::string bf::AssemblyInstructions::dataIncrement()
{
    return "   inc byte [edi]";
}


/*
* =============================================================
*
* Function responsible for decrementing the data at the instruction pointer
* Generates the code for it
*
* Return: std::string
*
* =============================================================
*/
std::string bf::AssemblyInstructions::dataDecrement()
{
    return "   dec byte [edi]";
}


/*
* =======================================
*
* Function responsible for input handling
* Generates the assembly code for it
*
* Return: std::string
*
* =======================================
*/
std::string bf::AssemblyInstructions::ioInput()
{
    // Mi a fasz
    std::string ret;
    ret += "   mov eax, 3\n";
    ret += "   mov ebx, 0\n";
    ret += "   mov ecx, [pointer]\n";
    ret += "   mov edx, 1\n";
    ret += "   int 0x80\n";

    return ret;
}
/*
mov eax, 3                ; syscall number for sys_read
mov ebx, 0                ; file descriptor for stdin
mov ecx, [pointer]        ; address of the current cell
mov edx, 1                ; number of bytes to read
int 0x80                  ; invoke system call to read character from stdin
*/


/*
* ==========================================================
* 
* Function responsible for handling the printing instruction
* Generates the code for it
*
* Return: std::string
*
* ==========================================================
*/
std::string bf::AssemblyInstructions::ioPrint()
{
    std::string ret;
    ret += "   mov eax, 4\n";
    ret += "   mov ebx, 1\n";
    ret += "   mov ecx, [pointer]\n";
    ret += "   mov edx, 1\n";
    ret += "   int 0x80\n";

    return ret;
}

/*
mov edx, 1                ; Length of the character to print
mov ecx, esp              ; Pointer to the character to print
mov eax, 4                ; syscall (write)
mov ebx, 1                ; File descriptor for stdout
int 0x80                  ; Invoke the operating system to write to stdout
*/


// TODO
std::string bf::AssemblyInstructions::loopBegin()
{
    return "Loop Begn";
}


// TODO
std::string bf::AssemblyInstructions::loopEnd()
{
    return "Loop End";
}