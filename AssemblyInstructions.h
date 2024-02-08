#ifndef ASSEMBLY_INSTRUCTIONS_H
#define ASSEMBLY_INSTRUCTIONS_H

#include <string>
#include <sstream>

namespace bf {

    class AssemblyInstructions {

        public:
            AssemblyInstructions() = default;
            ~AssemblyInstructions();
            
            // Assembly start, end
            std::string beginAssembly(uint32_t tapeSize);
            std::string endAssembly();

            // Instruction pointer manipulators
            std::string ptrMoveLeft();
            std::string ptrMoveRight();
            
            // Data manipulators
            std::string dataIncrement();
            std::string dataDecrement();

            // Input, output
            std::string ioInput();
            std::string ioPrint();

            // Loops
            std::string loopBegin();
            std::string loopEnd();
    };
}
#endif // !ASSEMBLY_INSTRUCTIONS_H