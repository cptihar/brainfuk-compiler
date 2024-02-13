#ifndef GENERATE_ASSEMBLY_H
#define GENERATE_ASSEMBLY_H

#include <stack>
#include <vector>
#include <fstream>
#include <functional>
#include <unordered_map>


#include "BrainfuckConstants.h"
#include "AssemblyInstructions.h"

namespace bf {

    class GenerateAssembly {
        public:
            GenerateAssembly(const std::vector<unsigned char>& instructions);
            ~GenerateAssembly();

            void createAssembly();
            void dumpAssembly(const char* fpath);

        private: // Variables, references

            // Const reference to the BF instructions
            const std::vector<unsigned char>&  m_BfInstructionRef;

            // Hash map which has functions for the bf instructions
            std::unordered_map<unsigned char, std::function<SVEC()>>  m_InstructionHashes;
            
            // Generated assembly code
            SVEC  m_GeneratedAssembly;

            // Assembly instruction object
            bf::AssemblyInstructions  m_AsmInstructions;

        private: // Functions
            void      m_initializeHashMap();
            uint32_t  m_calculateTapeSize();
            void      m_appendGeneratedCode(const SVEC& data);
            void      m_handleBfLoopInstruction(size_t loopStartIndex);
    };
}
#endif // !GENERATE_ASSEMBLY_H