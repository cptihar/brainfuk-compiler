#ifndef ASSEMBLY_INSTRUCTIONS_H
#define ASSEMBLY_INSTRUCTIONS_H

#include <string>
#include <vector>

#define SVEC  std::vector<std::string>

namespace bf {

    class AssemblyInstructions {
        public:
            AssemblyInstructions() = default;
            ~AssemblyInstructions();
            
            // Assembly start, end
            SVEC beginAssembly(uint32_t tapeSize);
            SVEC endAssembly();

            // Instruction pointer manipulators
            SVEC ptrMoveLeft();
            SVEC ptrMoveRight();
            
            // Data manipulators
            SVEC dataIncrement();
            SVEC dataDecrement();

            // Input, output
            SVEC ioInput();
            SVEC ioPrint();

            // Loops
            SVEC loopBegin(const std::string& jumpForward);
            SVEC loopEnd(const std::string& jumpBackPosition);
    };
}
#endif // !ASSEMBLY_INSTRUCTIONS_H